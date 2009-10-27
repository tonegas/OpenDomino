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

#define LARGHEZZA_FIN 1000
#define ALTEZZA_FIN  1000
#define BPP_FIN       32

#define GRIGLIA_EDITOR_Y 50
#define GRIGLIA_EDITOR_X 50

#define X_TELECAMERA 0
#define Y_TELECAMERA 0
#define H_TELECAMERA 150
#define FOVY    30
#define ZNEAR   5
#define ZFAR    500

#define LARGHEZZA_PEZZO 4
#define ALTEZZA_PEZZO 8
#define SPESSORE_PEZZO 2

#define LARGHEZZA_BASE 8
#define ALTEZZA_BASE 2
#define SPESSORE_BASE 8

#define H_PEZZO 2

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

class Pezzo {
    bool presente;
public:

    Pezzo(bool alive_aux = false) {
        presente = alive_aux;
    }

    void setAlive(bool alive_aux) {
        presente = alive_aux;
    }

    bool getAlive() {
        return presente;
    }
};

class Base {
    bool presente;
public:

    Base(bool alive_aux = false) {
        presente = alive_aux;
    }

    void setAlive(bool alive_aux) {
        presente = alive_aux;
    }

    bool getAlive() {
        return presente;
    }
};

class PosXYZoom {
public:
    GLfloat x;
    GLfloat y;
    GLfloat zoom;

    PosXYZoom(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 1) {
        x = x_aux;
        y = y_aux;
        zoom = zoom_aux;
    }
};

class MuoviGriglia {
public:
    GLfloat da_2d_a_3d;
    GLfloat delta_zoom;

    GLfloat start_t_x_2d;
    GLfloat start_t_y_2d;
    GLfloat t_x_2d;
    GLfloat t_y_2d;

    GLfloat t_x;
    GLfloat t_y;

    GLfloat z_x;
    GLfloat z_y;
    GLfloat z_zoom;

    MuoviGriglia(GLfloat da_2d_a_3d_aux, GLfloat delta_zoom_aux) {
        da_2d_a_3d = da_2d_a_3d_aux;
        delta_zoom = delta_zoom_aux;

        start_t_x_2d = 0;
        start_t_y_2d = 0;
        t_x_2d = 0;
        t_y_2d = 0;

        t_x = 0;
        t_y = 0;

        z_x = 0;
        z_y = 0;
        z_zoom = 1;
    }
};


//    void setGrigliaAuxZoom(GLfloat aux_zoom, GLfloat aux_zoom_x = 0, GLfloat aux_zoom_y = 0) {
//        griglia.t_aux_zoom = aux_zoom;
//        griglia.zoom_aux_x = aux_zoom_x;
//        griglia.zoom_aux_y = aux_zoom_y;
//    }
//
//    void setGrigliaAuxXY(GLfloat aux_x, GLfloat aux_y) {
//        griglia.t_aux_x = aux_x;
//        griglia.t_aux_y = aux_y;
//    }

class Griglia {
    PosXYZoom griglia;
    Pezzo matrice_pezzi[GRIGLIA_EDITOR_X][GRIGLIA_EDITOR_Y];
    Base matrice_basi[GRIGLIA_EDITOR_X][GRIGLIA_EDITOR_Y];
    int num_y_righe;
    int num_x_colonne;
public:

    Griglia(int num_x_colonne_aux, int num_y_righe_aux) {
        num_y_righe = num_y_righe_aux;
        num_x_colonne = num_x_colonne_aux;
        for (int i = 0; i < GRIGLIA_EDITOR_X; i++)
            for (int j = 0; j < GRIGLIA_EDITOR_Y; j++) {
                matrice_pezzi[i][j].setAlive(false);
                matrice_basi[i][j].setAlive(false);
            }
        //        matrice_pezzi = new Pezzo*[num_colonne];
        //   	for(int i=0;i<num_colonne;i++)
        //            matrice_pezzi[i] = new Pezzo[num_colonne];
    }

    ~Griglia() {
    }

    PosXYZoom getGriglia() {
        return griglia;
    }

    Pezzo& getPezzo(int i, int j) {
        return matrice_pezzi[i][j];
    }

    Base& getBase(int i, int j) {
        return matrice_basi[i][j];
    }

    void setGrigliaZoom(GLfloat zoom) {
        griglia.zoom = zoom;
    }

    void setGrigliaXY(GLfloat x, GLfloat y) {
        griglia.x = x;
        griglia.y = y;
    }
};

class Livello {
protected:
    Griglia livello_editor;
    MuoviGriglia muovi;

    bool bottone_sinistro, bottone_destro;
public:

    Livello(int num_x_colonne_aux, int num_y_righe_aux) :
    livello_editor(num_x_colonne_aux, num_y_righe_aux),
    muovi(2.0 * H_TELECAMERA * tan(FOVY / 2.0 / 180.0 * M_PI) / (GLfloat) ALTEZZA_FIN, 2) {
        bottone_destro = false;
        bottone_sinistro = false;

        //livello_editor.setGrigliaZoom(1.0);
        //livello_editor.setGrigliaAuxZoom(1.0);

        //h_finestra = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI);
        //l_finestra = ((GLfloat)ALTEZZA_FIN/(GLfloat)LARGHEZZA_FIN)*h_finestra;
    }

};

class Editor : public Livello {
    int num_x_colonne;
    int num_y_righe;
    GLfloat cubo_selezione[GRIGLIA_EDITOR_X][GRIGLIA_EDITOR_Y];

public:

    Editor(int num_y_righe_aux = GRIGLIA_EDITOR_Y, int num_x_colonne_aux = GRIGLIA_EDITOR_X) : Livello(num_x_colonne_aux, num_y_righe_aux) {
        num_y_righe = num_y_righe_aux;
        num_x_colonne = num_x_colonne_aux;
        for (int i = 0; i < GRIGLIA_EDITOR_X; i++)
            for (int j = 0; j < GRIGLIA_EDITOR_Y; j++)
                cubo_selezione[i][j] = 0;
    }

    void inizializzaEditor() {
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
                FOVY, /* field of view in degree */
                LARGHEZZA_FIN / ALTEZZA_FIN, /* aspect ratio */
                ZNEAR, /* Z near */
                ZFAR /* Z far */
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
    void stampaBasi(int x, int y);
    void stampaQuadrato(int x, int y, GLfloat attivo);

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

        //SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1); funziona solamento in fullscreen
        screen = SDL_SetVideoMode(larghezza, altezza, bpp, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_GL_SWAP_CONTROL);

        if (screen == NULL) {
            printf("ERRORE di creazione video SDL: %s.\n", SDL_GetError());
            exit(-1);
        }

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glEnable(GL_DEPTH_TEST); //questa andrà attivata


        domino_editor.inizializzaEditor();
    }

    void loop() {
        Uint32 inizio, fine;
        int durata, aspetto;

        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
        }
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

    int getFrames() {
        return frame_ms;
    }
};

int main(int argc, char** argv) {
    Gioco domino;
    domino.loop();
    SDL_Quit();
    return (EXIT_SUCCESS);
}

int Editor::stato(Gioco& gioco) {
    if (fabs(livello_editor.getGriglia().zoom - muovi.z_zoom) >= 0.01) {

        //cout << livello_editor.getGriglia().zoom << ' ' << muovi.z_zoom << '\n' << flush;

        livello_editor.setGrigliaXY(livello_editor.getGriglia().x + ((muovi.z_x - livello_editor.getGriglia().x) / 10),
                livello_editor.getGriglia().y + ((muovi.z_y - livello_editor.getGriglia().y) / 10));

        livello_editor.setGrigliaZoom(livello_editor.getGriglia().zoom + (muovi.z_zoom - livello_editor.getGriglia().zoom) / 10);
    }
    return 1;
}

void Editor::stampaSuperficeBase() {
    glPushMatrix();

    glTranslatef(0.0, 0.0, -0.001);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
    glVertex3f(num_x_colonne*ALTEZZA_PEZZO+ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
    glVertex3f(num_x_colonne*ALTEZZA_PEZZO+ALTEZZA_PEZZO, num_y_righe*ALTEZZA_PEZZO+ALTEZZA_PEZZO, 0);
    glVertex3f(-ALTEZZA_PEZZO, num_y_righe*ALTEZZA_PEZZO+ALTEZZA_PEZZO, 0);
    glEnd();

    glPopMatrix();
}

void Editor::stampaPezzo(int x, int y) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf + ((GLfloat) ALTEZZA_PEZZO / 2.0)-((GLfloat) SPESSORE_PEZZO / 2.0);
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;
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
    glTranslatef(sposto_x, sposto_y, H_PEZZO);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
    glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
    glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
    glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
    glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
    glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
    glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
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

void Editor::stampaBasi(int x, int y) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;
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
    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(SPESSORE_BASE, 0.0, 0.0);
    glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
    glVertex3f(0.0, ALTEZZA_BASE, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
    glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
    glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
    glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
    glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(SPESSORE_BASE, 0.0, 0.0);
    glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
    glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, ALTEZZA_BASE, 0.0);
    glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
    glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
    glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
    glVertex3f(0.0, ALTEZZA_BASE, 0.0);
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

void Editor::stampaQuadrato(int x, int y, GLfloat attivo) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;
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
    glColor4f(1.0f, 0, 0, attivo);
    glLineWidth(2.5);
    glScalef(0.98,0.98,0.98);
    glTranslatef(ALTEZZA_PEZZO*0.01,ALTEZZA_PEZZO*0.01,ALTEZZA_PEZZO*0.01);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
    glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
    glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
    glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
    glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
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
    for (int i = 0; i < num_x_colonne; i++) {
        for (int j = 0; j < num_y_righe; j++) {
            if (cubo_selezione[i][j] > 0) {
                stampaQuadrato(i, j, cubo_selezione[i][j]);
                cubo_selezione[i][j] -= 0.05;
            }
            if (livello_editor.getPezzo(i, j).getAlive() == 1) {
                stampaPezzo(i, j);
            }
            if (livello_editor.getBase(i, j).getAlive() == 1) {
                stampaBasi(i, j);
            }
        }
    }
    //for (int i = 0; i < 90; i++)stampaPezzo(i * 2);
    //stampaPezzo(0);
    glPopMatrix();
    SDL_GL_SwapBuffers();



    return 1;
}

int Editor::input(Gioco& gioco) {
    SDL_Event evento;
    SDL_PumpEvents();
    GLfloat mouse_x, mouse_y;
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            gameExit();
        }
        switch (evento.type) {
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        gameExit();
                        break;
                    case SDLK_PAGEUP:
                        if (gioco.getFrames() > 1)
                            gioco.setFrames(gioco.getFrames() - 1);
                        break;
                    case SDLK_PAGEDOWN:
                        gioco.setFrames(gioco.getFrames() + 1);
                        break;
                    case SDLK_3:
                        break;
                    case SDLK_4:
                        break;
                    case SDLK_5:
                        break;
                    case SDLK_6:
                        break;
                    case SDLK_7:
                        break;
                    default:
                        break;

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.button == SDL_BUTTON_LEFT) {
                    mouse_x = ((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * muovi.da_2d_a_3d - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom;
                    mouse_y = (((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * muovi.da_2d_a_3d - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom;
                    if ((unsigned) (mouse_x / (GLfloat) ALTEZZA_PEZZO) < GRIGLIA_EDITOR_X && (unsigned) (mouse_y / (GLfloat) ALTEZZA_PEZZO) < GRIGLIA_EDITOR_Y) {
                        if (livello_editor.getPezzo((unsigned) (mouse_x / (GLfloat) ALTEZZA_PEZZO), (unsigned) (mouse_y / (GLfloat) ALTEZZA_PEZZO)).getAlive()) {
                            livello_editor.getPezzo((unsigned) (mouse_x / (GLfloat) ALTEZZA_PEZZO), (unsigned) (mouse_y / (GLfloat) ALTEZZA_PEZZO)).setAlive(false);
                        } else {
                            livello_editor.getPezzo((unsigned) (mouse_x / (GLfloat) ALTEZZA_PEZZO), (unsigned) (mouse_y / (GLfloat) ALTEZZA_PEZZO)).setAlive(true);
                        }
                    }
                }
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    muovi.start_t_x_2d = evento.button.x;
                    muovi.start_t_y_2d = evento.button.y;
                    muovi.t_x = livello_editor.getGriglia().x;
                    muovi.t_y = livello_editor.getGriglia().y;
                    bottone_destro = true;
                }
                if (evento.button.button == SDL_BUTTON_WHEELUP) {
                    GLfloat zoom = livello_editor.getGriglia().zoom;
                    if (zoom * muovi.delta_zoom < 10) {
                        muovi.z_zoom = zoom * muovi.delta_zoom;
                        muovi.z_x = livello_editor.getGriglia().x + (1 - muovi.delta_zoom)*((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * muovi.da_2d_a_3d - livello_editor.getGriglia().x);
                        muovi.z_y = livello_editor.getGriglia().y + (1 - muovi.delta_zoom)*(((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * muovi.da_2d_a_3d - livello_editor.getGriglia().y);
                    }
                }
                if (evento.button.button == SDL_BUTTON_WHEELDOWN) {
                    /*
                    //_mouseX_3d_zoomNuovo_[posizione del mouse riportata in uno spazio 3d ed eliminato il fattore di zoom] = (((_mouseX_[coordinate della finestra asse x verso destra asse y verso basso]-_LARGHEZZA_FIN/2_[perchè la telecamera punta in (zero[x],zero[y]) che qundi si trova a metà finestra])*
                    //_da_2d_a_3d_[variabile che riporta la mia distanza sulla finestra in una distanza 3d vedi formula sopra] - _x_[posizione x assoluta della griglia])/ _zoomNuovo_[successivo livello di zoom])

                    //_mouseY_3d_zoomNuovo_[posizione del mouse riportata in uno spazio 3d ed eliminato il fattore di zoom] = (((_ALTEZZA_FIN/2_[perchè la telecamera punta in (zero[x],zero[y]) che qundi si trova a metà finestra] - _mouseY_[coordinate della finestra asse x verso destra asse y verso basso])*
                    //_da_2d_a_3d_[variabile che riporta la mia distanza sulla finestra in una distanza 3d vedi formula sopra] - _y_[posizione y assoluta della griglia])/ _zoomNuovo_[successivo livello di zoom])

                    //formula per determinare il movimento della griglia quando essa viene zoommata (_x_+_zoomNuovo_*((_mouseX_3d_zoomNuovo_)-(_mouseX_3d_zoomVecchio_)))
                    //(_y_+_zoomNuovo_*((_mouseY_3d_zoomNuovo_)-(_mouseY_3d_zoomVecchio_)))

                     //livello_editor.setGrigliaXY(livello_editor.getGriglia().x + (livello_editor.getGriglia().zoom-0.1)*((((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x) / (livello_editor.getGriglia().zoom-0.1))-(((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * da_2d_a_3d - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom)),
                     //        livello_editor.getGriglia().y +(livello_editor.getGriglia().zoom-0.1)*((((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y) / (livello_editor.getGriglia().zoom-0.1)-(((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * da_2d_a_3d - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom));
                     */
                    GLfloat zoom = livello_editor.getGriglia().zoom;
                    if (zoom / muovi.delta_zoom > 0.1) {
                        muovi.z_zoom = zoom / muovi.delta_zoom;
                        muovi.z_x = livello_editor.getGriglia().x + ((muovi.delta_zoom - 1) / muovi.delta_zoom)*((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * muovi.da_2d_a_3d - livello_editor.getGriglia().x);
                        muovi.z_y = livello_editor.getGriglia().y + ((muovi.delta_zoom - 1) / muovi.delta_zoom)*(((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * muovi.da_2d_a_3d - livello_editor.getGriglia().y);
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                mouse_x = ((evento.button.x - (GLfloat) LARGHEZZA_FIN / 2) * muovi.da_2d_a_3d - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom;
                mouse_y = (((GLfloat) ALTEZZA_FIN / 2 - evento.button.y) * muovi.da_2d_a_3d - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom;
                if ((unsigned) (mouse_x / (GLfloat) ALTEZZA_PEZZO) < GRIGLIA_EDITOR_X && (unsigned) (mouse_y / (GLfloat) ALTEZZA_PEZZO) < GRIGLIA_EDITOR_Y)
                    cubo_selezione[(unsigned) (mouse_x / (GLfloat) ALTEZZA_PEZZO)][(unsigned) (mouse_y / (GLfloat) ALTEZZA_PEZZO)] = 1;
                if (bottone_destro) {
                    muovi.t_x_2d = evento.button.x - muovi.start_t_x_2d;
                    muovi.t_y_2d = evento.button.y - muovi.start_t_y_2d;
                    livello_editor.setGrigliaXY(muovi.t_x + (muovi.t_x_2d * muovi.da_2d_a_3d), muovi.t_y - (muovi.t_y_2d * muovi.da_2d_a_3d));
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