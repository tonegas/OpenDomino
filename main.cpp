/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

#define FRAMERATE   50                  //frame per secondo massimi
#define FRAMEMS     1000/FRAMERATE      //millisecondi per frame

#define LARGHEZZA_FIN 1200
#define ALTEZZA_FIN  1024
#define BPP_FIN       32

#define GRIGLIA_EDITOR_Y 20
#define GRIGLIA_EDITOR_X 25


#define LARGHEZZA 4
#define ALTEZZA 8
#define SPESSORE 2

//
//GLfloat rx = 0;
//GLfloat ry = 0;
//GLfloat rz = 0;
//GLfloat startx = 0;
//GLfloat starty = 0;
//GLfloat jump = 0;

enum Stato {
    MENU,
    PARTITA,
    EDITOR_COSTRUISCI,
    EDITOR_TEST
};

const GLfloat cavalier[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    -0.5, -0.5, 1, 0,
    0, 0, 0, 1
};

//quando passa a false il gioco si chiude
bool alive;

void gameExit() {
    alive = false;
}

class Gioco;

class PosOri {
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat rx;
    GLfloat ry;
    GLfloat rz;

    PosOri(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat z_aux = 0, GLfloat rx_aux = 0, GLfloat ry_aux = 0, GLfloat rz_aux = 0) {
        x = x_aux;
        y = y_aux;
        z = z_aux;
        rx = rx_aux;
        ry = ry_aux;
        rz = rz_aux;
    }

};

class Livello {
    PosOri Telecamera;
    int num_righe;
    int num_colonne;
    //Posto matrice_posti[NUM_RIGHE][NUM_COLONNE];
public:

    Livello(int num_righe_aux, int num_colonne_aux, GLfloat posizione_x_telecamera, GLfloat posizione_y_telecamera, GLfloat altezza_telecamera) {
        num_righe = num_righe_aux;
        num_colonne = num_colonne_aux;
        Telecamera.x = posizione_x_telecamera;
        Telecamera.y = posizione_y_telecamera;
        Telecamera.z = altezza_telecamera;
    }

    PosOri getTelecamera() {
        return Telecamera;
    }
};

class Editor {
    Livello livello_editor;
    int num_righe;
    int num_colonne;

    GLfloat start_tx, start_ty, final_tx, final_ty;
    GLfloat tx, ty;

    bool bottone_sinistro, bottone_destro;

    bool cambio_zoom;
    GLfloat zzz;

public:

    Editor(int num_righe_aux = GRIGLIA_EDITOR_Y, int num_colonne_aux = GRIGLIA_EDITOR_X) : livello_editor(num_righe_aux, num_colonne_aux, (num_colonne_aux * ALTEZZA) / 2, (num_righe_aux * ALTEZZA) / 2, 400) {
        num_righe = num_righe_aux;
        num_colonne = num_colonne_aux;
        tx = 0;
        ty = 0;
        bottone_destro = false;
        bottone_sinistro = false;

        cambio_zoom = false;
        zzz = 150;
    }

    void inizializzaLivello() {
        //glViewport(0,0,LARGHEZZA_FIN,ALTEZZA_FIN);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluPerspective(45,LARGHEZZA_FIN/ALTEZZA_FIN,0.1,100);
        //        glOrtho(0, ((GLfloat) num_colonne * (GLfloat) ALTEZZA),
        //                0, ((GLfloat) num_righe * (GLfloat) ALTEZZA) / ((GLfloat) LARGHEZZA_FIN / (GLfloat) ALTEZZA_FIN),
        //                100, 200); //misure rispetto alla posizione dell'occhio
        // glMultMatrixf(cavalier);

        gluPerspective
                (
                40.0, /* field of view in degree */
                1.0, /* aspect ratio */
                5.0, /* Z near */
                200.0 /* Z far */
                );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(
                0, 0, 150, /* eye  */
                0, 0, 0.0, /* center  */
                0.0, 1.0, 0.0); /* up is in positive Y direction */
    }

    int stato(Gioco& gioco);
    int video(Gioco& gioco);
    int input(Gioco& gioco);

    void stampaSuperficeBase();
    void stampaPezzo(int x, int y);

};

class Gioco {
    //parametri finestra
    int larghezza;
    int altezza;
    int bpp;

    //superfice della finestra
    SDL_Surface *screen;

    //stato del gioco
    Stato stato;

    //variabile per la modifica della velocità di gioco
    int frame_ms;

    //giocatore
    //Giocatore giocatore;

    //Oggetto editor per la gestione della grafica della partita
    Editor domino_editor;

public:

    Gioco() {

        larghezza = LARGHEZZA_FIN;
        altezza = ALTEZZA_FIN;
        bpp = BPP_FIN;

        stato = EDITOR_COSTRUISCI;
        alive = true;
        frame_ms = FRAMEMS;

        if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
            printf("ERRORE di inizializzazione SDL: %s.\n", SDL_GetError());
            exit(-1);
        }

        screen = SDL_SetVideoMode(larghezza, altezza, bpp, SDL_HWSURFACE | SDL_OPENGL | SDL_DOUBLEBUF);
        if (screen == NULL) {
            printf("ERRORE di creazione video SDL: %s.\n", SDL_GetError());
            exit(-1);
        }

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

        domino_editor.inizializzaLivello();
    }

    void loop() {
        Uint32 inizio, fine;
        int durata, aspetto;
        while (alive) {
            inizio = SDL_GetTicks();

            domino_editor.input((*this));
            domino_editor.stato((*this));
            domino_editor.video((*this));
            //    SDL_Flip(screen);

            fine = SDL_GetTicks();
            durata = fine - inizio;
            aspetto = frame_ms - durata;
            if (aspetto > 0)
                SDL_Delay(aspetto);
            //            else
            //                cout << "H" << flush;

            //        if(SDL_GetTicks() - tempo > 1000){
            //            tempo = SDL_GetTicks();
            //            cout<<frame<<' '<<flush;
            //            frame=0;
            //        }
            //        frame++;
            //        input(&evento);
            //        stato();
            //        video();
        }
    }

    void setFrames(GLfloat frame_aux) {
        frame_ms = frame_aux;
    }
};

int main(int argc, char** argv) {
    Gioco domino;
    domino.loop();
    SDL_Quit();
    return (EXIT_SUCCESS);
}

int Editor::stato(Gioco& gioco) {
    return 1;
}

void Editor::stampaSuperficeBase() {
    glPushMatrix();

    glColor3f(1.0f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(num_colonne*ALTEZZA, 0, 0);
    glVertex3f(num_colonne*ALTEZZA, num_righe*ALTEZZA, 0);
    glVertex3f(0, num_righe*ALTEZZA, 0);
    glEnd();

    glPopMatrix();
}

void Editor::stampaPezzo(int x, int y) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA) * xf + ((GLfloat) ALTEZZA / 2.0)-((GLfloat) SPESSORE / 2.0);
    GLfloat sposto_y = ((GLfloat) ALTEZZA) * yf;
    //    /* clear screen */
    //
    //    glPushMatrix();
    //
    //    /* affine transformations */
    //    glRotatef(rx, 1.0, 0.0, 0.0);
    //    glRotatef(ry, 0.0, 1.0, 0.0);
    //    glRotatef(rz, 0.0, 0.0, 1.0);
    //
    //    /* orientation vectors */
    //    glBegin(GL_LINES);
    //    glColor3f(1, 0, 0);
    //    glVertex3f(0, 0, 0);
    //    glVertex3f(1, 0, 0);
    //    glColor3f(0, 1, 0);
    //    glVertex3f(0, 0, 0);
    //    glVertex3f(0, 1, 0);
    //    glColor3f(0, 0, 1);
    //    glVertex3f(0, 0, 0);
    //    glVertex3f(0, 0, 1);
    //    glEnd();
    //
    //    /* base quad */
    //    // 		glColor3f(0.2f,0.2f,0.2f);
    //    // 		glBegin(GL_QUADS );
    //    // 			glVertex3f(-10,-5,-10);
    //    // 			glVertex3f(+10,-5,-10);
    //    // 			glVertex3f(+10,-5,+10);
    //    // 			glVertex3f(-10,-5,+10);
    //    // 		glEnd();
    //
    //    /* wire cube */
    glPushMatrix();
    glTranslatef(sposto_x, sposto_y, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(SPESSORE, 0.0, 0.0);
    glVertex3f(SPESSORE, ALTEZZA, 0.0);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, LARGHEZZA);
    glVertex3f(SPESSORE, 0.0, LARGHEZZA);
    glVertex3f(SPESSORE, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, 0.0, LARGHEZZA);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(SPESSORE, 0.0, 0.0);
    glVertex3f(SPESSORE, 0.0, LARGHEZZA);
    glVertex3f(0.0, 0.0, LARGHEZZA);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glVertex3f(SPESSORE, ALTEZZA, 0.0);
    glVertex3f(SPESSORE, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glEnd();
    //    // 			glColor3f(0.0f,1.0f,1.0f);
    //    // 			glBegin(GL_QUADS );
    //    // 				glVertex3f(0,-5,-5);
    //    // 				glVertex3f(+1,-5,-5);
    //    // 				glVertex3f(+1,-5,+5);
    //    // 				glVertex3f(0,-5,+5);
    //    // 			glEnd();
    //    // 			glBegin(GL_QUADS );
    //    // 				glVertex3f(+1,-5,-5);
    //    // 				glVertex3f(+1,-5,+5);
    //    // 				glVertex3f(+1,+5,+5);
    //    // 				glVertex3f(+1,+5,-5);
    //    // 			glEnd();
    //    // 			glBegin(GL_QUADS );
    //    // 				glVertex3f(+1,-5,+5);
    //    // 				glVertex3f(+1,+5,+5);
    //    // 				glVertex3f(0,+5,+5);
    //    // 				glVertex3f(0,-5,+5);
    //    // 			glEnd();
    //    // 			glBegin(GL_QUADS );
    //    // 				glVertex3f(+5,+5,+5);
    //    // 				glVertex3f(-5,+5,+5);
    //    // 				glVertex3f(-5,+5,-5);
    //    // 				glVertex3f(+5,+5,-5);
    //    // 			glEnd();
    //    glPopMatrix();
    //
    glPopMatrix();
    //    /* double buffering! */
}

int Editor::video(Gioco& gioco) {

    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );
    if (cambio_zoom) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(
                0, 0, zzz, /* eye  */
                0, 0, 0.0, /* center  */
                0.0, 1.0, 0.0); /* up is in positive Y direction */
        cambio_zoom=false;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(tx / 6.0, -ty / 7.5, 0); //questi valori sono perfetti con glOrto() ma non fanno bene in prospettiva
    stampaSuperficeBase();
    for (int i = 0; i < num_colonne; i++)
        for (int j = 0; j < num_righe; j++)
            stampaPezzo(i, j);
    //for (int i = 0; i < 90; i++)stampaPezzo(i * 2);
    //stampaPezzo(0);
    glPopMatrix();
    SDL_GL_SwapBuffers();



    return 1;
}

int Editor::input(Gioco& gioco) {
    SDL_Event evento;
    SDL_PumpEvents();
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            gameExit();
        }
        switch (evento.type) {
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_q:
                        zzz++;
                        break;
                    case SDLK_a:
                        zzz--;
                        break;
                    case SDLK_2:
                        gioco.setFrames(FRAMEMS * 10);
                        break;
                    case SDLK_3:
                        gioco.setFrames(FRAMEMS * 5);
                        break;
                    case SDLK_4:
                        gioco.setFrames(FRAMEMS * 2);
                        break;
                    case SDLK_5:
                        gioco.setFrames(FRAMEMS);
                        break;
                    case SDLK_6:
                        gioco.setFrames(FRAMEMS / 5);
                        break;
                    case SDLK_7:
                        gioco.setFrames(FRAMEMS / 10);
                        break;
                    default:
                        break;

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    start_tx = evento.button.x;
                    start_ty = evento.button.y;
                    bottone_destro = true;
                }
                if (evento.button.button == SDL_BUTTON_WHEELUP) {
                    zzz+=10;
                    cambio_zoom = true;
                }
                if (evento.button.button == SDL_BUTTON_WHEELDOWN) {
                    zzz-=10;
                    cambio_zoom = true;
                }
                break;
            case SDL_MOUSEMOTION:
                if (bottone_destro) {
                    tx = final_tx + evento.button.x - start_tx;
                    ty = final_ty + evento.button.y - start_ty;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    final_tx = tx;
                    final_ty = ty;
                    start_tx = 0;
                    start_ty = 0;
                    bottone_destro = false;
                }
                break;
            default:
                break;
        }

    }
    return 1;
}