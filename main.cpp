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
#define ALTEZZA_FIN  300
#define BPP_FIN       32

#define GRIGLIA_EDITOR_Y 100
#define GRIGLIA_EDITOR_X 200
#define H_TELECAMERA 150

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

class PosZoom {
public:
    //assolute
    GLfloat x;
    GLfloat y;
    GLfloat zoom;

    //appoggio relative
    GLfloat t_aux_x;
    GLfloat t_aux_y;
    GLfloat zoom_aux_x;
    GLfloat zoom_aux_y;
    GLfloat t_aux_zoom;

    PosZoom(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 0) {
        x = x_aux;
        y = y_aux;
        zoom = zoom_aux;
        t_aux_x = t_aux_y = zoom_aux_x = zoom_aux_y = t_aux_zoom = 0;
    }

};

class Livello {
    PosZoom griglia;
    int num_righe;
    int num_colonne;
    //Posto matrice_posti[NUM_RIGHE][NUM_COLONNE];
public:

    Livello(int num_righe_aux, int num_colonne_aux) {
        num_righe = num_righe_aux;
        num_colonne = num_colonne_aux;
    }

    PosZoom getGriglia() {
        return griglia;
    }

    void setGrigliaZoom(GLfloat zoom) {
        griglia.zoom = zoom;
    }

    void setGrigliaAuxZoom(GLfloat aux_zoom,GLfloat aux_zoom_x=0,GLfloat aux_zoom_y=0) {
        griglia.t_aux_zoom = aux_zoom;
        griglia.zoom_aux_x = aux_zoom_x;
        griglia.zoom_aux_y = aux_zoom_y;
    }

    void setGrigliaXY(GLfloat x, GLfloat y) {
        griglia.x = x;
        griglia.y = y;
    }

    void setGrigliaAuxXY(GLfloat aux_x, GLfloat aux_y) {
        griglia.t_aux_x = aux_x;
        griglia.t_aux_y = aux_y;
    }
};

class Editor {
    Livello livello_editor;
    int num_righe;
    int num_colonne;

    GLfloat start_tx, start_ty, final_tx, final_ty;
    GLfloat tx, ty;

    bool bottone_sinistro, bottone_destro;

    GLfloat da_2d_a_3d;
    GLfloat fovy; //angolo y di visuale
    GLfloat z_near; //angolo y di visuale
    GLfloat z_far; //angolo y di visuale

    int prova_x,prova_y;

    GLfloat delta_zoom;

public:

    Editor(int num_righe_aux = GRIGLIA_EDITOR_Y, int num_colonne_aux = GRIGLIA_EDITOR_X) : livello_editor(num_righe_aux, num_colonne_aux) {
        num_righe = num_righe_aux;
        num_colonne = num_colonne_aux;

        tx = 0;
        ty = 0;

        bottone_destro = false;
        bottone_sinistro = false;

        fovy = 30.0; //angolo y di visuale
        z_near = 5.0; //angolo y di visuale
        z_far = 500.0; //angolo y di visuale

        delta_zoom=2;

        livello_editor.setGrigliaZoom(1.0);
        livello_editor.setGrigliaAuxZoom(1.0);

        //h_finestra = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI);
        //l_finestra = ((GLfloat)ALTEZZA_FIN/(GLfloat)LARGHEZZA_FIN)*h_finestra;

        da_2d_a_3d = 2.0 * H_TELECAMERA * tan(fovy / 2.0 / 180.0 * M_PI) / (GLfloat) ALTEZZA_FIN;
    }

    void inizializzaLivello() {
        //glViewport(0,0,LARGHEZZA_FIN,ALTEZZA_FIN);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //      gluPerspective(45,LARGHEZZA_FIN/ALTEZZA_FIN,0.1,100);
        //                glOrtho(0, ((GLfloat) num_colonne * (GLfloat) ALTEZZA),
        //                        0, ((GLfloat) num_righe * (GLfloat) ALTEZZA) / ((GLfloat) LARGHEZZA_FIN / (GLfloat) ALTEZZA_FIN),
        //                        100, 200); //misure rispetto alla posizione dell'occhio
        //         glMultMatrixf(cavalier);

        gluPerspective
                (
                fovy, /* field of view in degree */
                LARGHEZZA_FIN / ALTEZZA_FIN, /* aspect ratio */
                z_near, /* Z near */
                z_far /* Z far */
                );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(
                0.0, 0.0, H_TELECAMERA, /* eye  */
                0.0, 0.0, 0.0, /* center  */
                0.0, 1.0, 0.0); /* up is in positive Y direction */
    }

    int stato(Gioco& gioco);
    int video(Gioco& gioco);
    int input(Gioco& gioco);

    void stampaSuperficeBase();
    void stampaPezzo(int x, int y);
    void stampaQuadrato(int x, int y);

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

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
        SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1);

        screen = SDL_SetVideoMode(larghezza, altezza, bpp, SDL_HWSURFACE | SDL_OPENGL);



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
    if(fabs(livello_editor.getGriglia().zoom - livello_editor.getGriglia().t_aux_zoom) >= 0.001 ){
        cout<<livello_editor.getGriglia().zoom<<' '<<livello_editor.getGriglia().t_aux_zoom<<'\n'<<flush;
        livello_editor.setGrigliaXY(livello_editor.getGriglia().x+((livello_editor.getGriglia().zoom_aux_x-livello_editor.getGriglia().x)/10),
                livello_editor.getGriglia().y+((livello_editor.getGriglia().zoom_aux_y-livello_editor.getGriglia().y)/10));
        livello_editor.setGrigliaZoom(livello_editor.getGriglia().zoom+(livello_editor.getGriglia().t_aux_zoom-livello_editor.getGriglia().zoom)/10);
    }
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

void Editor::stampaQuadrato(int x, int y) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA) * xf;
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
    glVertex3f(ALTEZZA, 0.0, 0.0);
    glVertex3f(ALTEZZA, ALTEZZA, 0.0);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, ALTEZZA);
    glVertex3f(ALTEZZA, 0.0, ALTEZZA);
    glVertex3f(ALTEZZA, ALTEZZA, ALTEZZA);
    glVertex3f(0.0, ALTEZZA, ALTEZZA);
    glVertex3f(0.0, 0.0, ALTEZZA);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(ALTEZZA, 0.0, 0.0);
    glVertex3f(ALTEZZA, 0.0, ALTEZZA);
    glVertex3f(0.0, 0.0, ALTEZZA);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glVertex3f(ALTEZZA, ALTEZZA, 0.0);
    glVertex3f(ALTEZZA, ALTEZZA, ALTEZZA);
    glVertex3f(0.0, ALTEZZA, ALTEZZA);
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
    //    if (cambio_zoom) {
    //        h_finestra = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI);
    //        l_finestra = ((GLfloat)ALTEZZA_FIN/(GLfloat)LARGHEZZA_FIN)*h_finestra;
    //
    //        da_2d_a_3d = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI) / (GLfloat)ALTEZZA_FIN;
    //        glMatrixMode(GL_MODELVIEW);
    //        glLoadIdentity();
    //        gluLookAt(
    //                0, 0, h_telecamera, /* eye  */
    //                0, 0, 0.0, /* center  */
    //                0.0, 1.0, 0.0); /* up is in positive Y direction */
    //        cambio_zoom=false;
    //    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(livello_editor.getGriglia().x, livello_editor.getGriglia().y, 0);
    glScalef(livello_editor.getGriglia().zoom, livello_editor.getGriglia().zoom, livello_editor.getGriglia().zoom);

    stampaSuperficeBase();
    for (int i = 0; i < num_colonne; i++)
        for (int j = 0; j < num_righe; j++)
            if(prova_x==i && prova_y==j)
                stampaQuadrato(i, j);
    //for (int i = 0; i < 90; i++)stampaPezzo(i * 2);
    //stampaPezzo(0);
    glPopMatrix();
    SDL_GL_SwapBuffers();



    return 1;
}

int Editor::input(Gioco& gioco) {
    SDL_Event evento;
    SDL_PumpEvents();
    GLfloat mouse_x,mouse_y;
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            gameExit();
        }
        switch (evento.type) {
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_q:
                        break;
                    case SDLK_a:
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
                if (evento.button.button == SDL_BUTTON_LEFT) {
                    mouse_x = ((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom;
                    mouse_y = (((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom;
                    prova_x=(int) (mouse_x / (GLfloat) ALTEZZA);
                    prova_y=(int) (mouse_y / (GLfloat) ALTEZZA);
                }
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    start_tx = evento.button.x;
                    start_ty = evento.button.y;
                    livello_editor.setGrigliaAuxXY(livello_editor.getGriglia().x, livello_editor.getGriglia().y);
                    bottone_destro = true;
                }
                if (evento.button.button == SDL_BUTTON_WHEELUP) {

                    GLfloat zoom = livello_editor.getGriglia().zoom;
                    if(zoom * delta_zoom < 10){
                    livello_editor.setGrigliaAuxZoom(zoom * delta_zoom,livello_editor.getGriglia().x + (1 - delta_zoom)*((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x),
                            livello_editor.getGriglia().y + (1- delta_zoom)*(((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y));
                    }
                }
                if (evento.button.button == SDL_BUTTON_WHEELDOWN) {

                    //_mouseX_3d_zoomNuovo_[posizione del mouse riportata in uno spazio 3d ed eliminato il fattore di zoom] = (((_mouseX_[coordinate della finestra asse x verso destra asse y verso basso]-_LARGHEZZA_FIN/2_[perchè la telecamera punta in (zero[x],zero[y]) che qundi si trova a metà finestra])*
                    //_da_2d_a_3d_[variabile che riporta la mia distanza sulla finestra in una distanza 3d vedi formula sopra] - _x_[posizione x assoluta della griglia])/ _zoomNuovo_[successivo livello di zoom])

                    //_mouseY_3d_zoomNuovo_[posizione del mouse riportata in uno spazio 3d ed eliminato il fattore di zoom] = (((_ALTEZZA_FIN/2_[perchè la telecamera punta in (zero[x],zero[y]) che qundi si trova a metà finestra] - _mouseY_[coordinate della finestra asse x verso destra asse y verso basso])*
                    //_da_2d_a_3d_[variabile che riporta la mia distanza sulla finestra in una distanza 3d vedi formula sopra] - _y_[posizione y assoluta della griglia])/ _zoomNuovo_[successivo livello di zoom])

                    //formula per determinare il movimento della griglia quando essa viene zoommata (_x_+_zoomNuovo_*((_mouseX_3d_zoomNuovo_)-(_mouseX_3d_zoomVecchio_)))
                    //(_y_+_zoomNuovo_*((_mouseY_3d_zoomNuovo_)-(_mouseY_3d_zoomVecchio_)))

                    GLfloat zoom = livello_editor.getGriglia().zoom;
                    if(zoom / delta_zoom > 0.1){
                    //livello_editor.setGrigliaXY(livello_editor.getGriglia().x + (livello_editor.getGriglia().zoom-0.1)*((((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x) / (livello_editor.getGriglia().zoom-0.1))-(((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom)),
                    //        livello_editor.getGriglia().y +(livello_editor.getGriglia().zoom-0.1)*((((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y) / (livello_editor.getGriglia().zoom-0.1)-(((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom));

                    livello_editor.setGrigliaAuxZoom(zoom / delta_zoom,livello_editor.getGriglia().x + ((delta_zoom-1) / delta_zoom)*((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x),
                            livello_editor.getGriglia().y + ((delta_zoom-1) / delta_zoom)*(((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y));
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                    mouse_x = ((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom;
                    mouse_y = (((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom;
                    prova_x=(int) (mouse_x / (GLfloat) ALTEZZA);
                    prova_y=(int) (mouse_y / (GLfloat) ALTEZZA);
                if (bottone_destro) {
                    tx = evento.button.x - start_tx;
                    ty = evento.button.y - start_ty;
                    livello_editor.setGrigliaXY(livello_editor.getGriglia().t_aux_x + (tx * da_2d_a_3d), livello_editor.getGriglia().t_aux_y - (ty * da_2d_a_3d));
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    bottone_destro = false;
                }
                break;
            default:
                break;
        }

    }
    return 1;
}