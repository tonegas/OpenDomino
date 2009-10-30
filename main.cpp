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
#define LARGHEZZA_FIN_EDITOR 1000
#define ALTEZZA_FIN_EDITOR  1000
#define BPP_FIN       32

#define GRIGLIA_EDITOR_Y 50
#define GRIGLIA_EDITOR_X 50

#define X_TELECAMERA 0
#define Y_TELECAMERA 0
#define H_TELECAMERA 150
#define FOVY    40
#define ZNEAR   5
#define ZFAR    700

#define LIMITE_SUPERIORE_ZOOM 10
#define LIMITE_INFERIORE_ZOOM 0.5
#define DELTA_ZOOM 2.0

#define LARGHEZZA_PEZZO 4
#define ALTEZZA_PEZZO 8
#define SPESSORE_PEZZO 2

#define LARGHEZZA_BASE 8
#define ALTEZZA_BASE 2
#define SPESSORE_BASE 8

#define POSIZIONE_SUPERFICE -0.001

#define Z_PEZZO 2

//
//GLfloat rx = 0;
//GLfloat ry = 0;
//GLfloat rz = 0;
//GLfloat startx = 0;
//GLfloat starty = 0;
//GLfloat jump = 0;

enum Proiezione {
    ASSIONOMETRICA, PROSPETTICA
};

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
    PosXYZoom aux_griglia;
    //MuoviGriglia muovi;

    bool bottone_sinistro, bottone_destro;

    GLdouble matrice_model[16];
    GLdouble matrice_proj[16];
    GLint matrice_view[4];

    GLdouble superfice_z;
    GLdouble pos_x, pos_y, pos_z;
    GLdouble pos_x_iniziali, pos_y_iniziali;

    int mouse_x_fin, mouse_y_fin;
    int pos_x_griglia, pos_y_griglia;
    bool pos_griglia_ok;


public:

    Livello(int num_x_colonne_aux, int num_y_righe_aux) :
    livello_editor(num_x_colonne_aux, num_y_righe_aux) {
        bottone_destro = false;
        bottone_sinistro = false;

        //livello_editor.setGrigliaZoom(1.0);
        //livello_editor.setGrigliaAuxZoom(1.0);

        //h_finestra = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI);
        //l_finestra = ((GLfloat)ALTEZZA_FIN/(GLfloat)LARGHEZZA_FIN)*h_finestra;
    }

    //    void getMousePosXY(int mouse_x_fin_aux, int mouse_y_fin_aux) {
    //        mouse_x_fin = mouse_x_fin_aux;
    //        mouse_y_fin = mouse_y_fin_aux;
    //        getMousePosXY();
    //    }
    //
    //    void getMousePosXY() {
    //        gluUnProject(mouse_x_fin, ALTEZZA_FIN - mouse_y_fin, superfice_z, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
    //        pos_x = (pos_x - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom;
    //        pos_y = (pos_y - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom;
    //    }

    bool getMousePosGrigliaXY(int larghezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux) {
        mouse_x_fin = mouse_x_fin_aux;
        mouse_y_fin = mouse_y_fin_aux;
        return getMousePosGrigliaXY(larghezza_fin);
    }

    bool getMousePosGrigliaXY(int larghezza_fin) {
        gluUnProject(mouse_x_fin, larghezza_fin - mouse_y_fin, superfice_z, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
        pos_x_griglia = (int) (((pos_x - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom) / (GLfloat) ALTEZZA_PEZZO);
        pos_y_griglia = (int) (((pos_y - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom) / (GLfloat) ALTEZZA_PEZZO);
        if (pos_x_griglia >= 0 && pos_y_griglia >= 0 && pos_x_griglia < GRIGLIA_EDITOR_X && (unsigned) pos_y_griglia < GRIGLIA_EDITOR_Y) {
            pos_griglia_ok = true;
        } else {
            pos_griglia_ok = false;
        }
        return pos_griglia_ok;
    }

};

GLfloat coloryellow[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat colorblue [] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat colorgreen [] = {0.0f, 1.0f, 0.0f, 1.0f};
GLfloat colorwhite [] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightpos[] = {0, 0, 0, 1};
GLfloat lightpos_ambient[] = {60, 100, 120, 0};

class Editor : public Livello {
    int num_x_colonne;
    int num_y_righe;
    bool posiziona_pezzi,posiziona_basi;
    int posiziona_continua;

    Gioco *gioco;

    Proiezione tipo_proiezione;

    GLfloat cubo_selezione[GRIGLIA_EDITOR_X][GRIGLIA_EDITOR_Y];

public:

    Editor(int num_y_righe_aux = GRIGLIA_EDITOR_Y, int num_x_colonne_aux = GRIGLIA_EDITOR_X) : Livello(num_x_colonne_aux, num_y_righe_aux) {
        num_y_righe = num_y_righe_aux;
        num_x_colonne = num_x_colonne_aux;
        posiziona_pezzi = true;
        posiziona_continua=0;
        for (int i = 0; i < GRIGLIA_EDITOR_X; i++)
            for (int j = 0; j < GRIGLIA_EDITOR_Y; j++)
                cubo_selezione[i][j] = 0;
    }

    void inizializzaEditor(Gioco *gioco_aux) {
        tipo_proiezione = ASSIONOMETRICA;
        gioco = gioco_aux;

        setProiezione(tipo_proiezione, LARGHEZZA_FIN_EDITOR, ALTEZZA_FIN_EDITOR);

        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, colorwhite);
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, colorwhite);
        glLightfv(GL_LIGHT1, GL_POSITION, lightpos_ambient);
    }

    int stato();
    int video();
    int input();

    void setProiezione(Proiezione tipo, int larghezza_fin, int altezza_fin) {
        tipo_proiezione = tipo;
        glViewport(0, 0, (GLint) larghezza_fin, (GLint) altezza_fin);
        switch (tipo_proiezione) {
            case ASSIONOMETRICA:
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0, ((GLfloat) num_x_colonne * (GLfloat) ALTEZZA_PEZZO),
                        0, ((GLfloat) num_y_righe * (GLfloat) ALTEZZA_PEZZO) / ((GLfloat) larghezza_fin / (GLfloat) altezza_fin),
                        ZNEAR, ZFAR); //misure rispetto alla posizione dell'occhio
                glMultMatrixf(cavalier);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(
                        0.0, 0.0, H_TELECAMERA, /* eye  */
                        0.0, 0.0, 0.0, /* center  */
                        0.0, 1.0, 0.0); /* up is in positive Y direction */

                break;
            case PROSPETTICA:
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(FOVY, (GLfloat) larghezza_fin / (GLfloat) altezza_fin, ZNEAR, ZFAR);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(
                        0.0, 0.0, H_TELECAMERA * 3.5, /* eye  */
                        0.0, 0.0, 0.0, /* center  */
                        0.0, 1.0, 0.0); /* up is in positive Y direction */

                break;
        }

        glGetIntegerv(GL_VIEWPORT, matrice_view);
        glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model);
        glGetDoublev(GL_PROJECTION_MATRIX, matrice_proj);

        //recupero pa posizione z della superfice
        GLdouble mouse_x, mouse_y;
        gluProject(0.0, 0.0, 0.0, matrice_model, matrice_proj, matrice_view, &mouse_x, &mouse_y, &superfice_z);
    }

    void stampaSuperficeBase();
    void stampaPezzo(int x, int y);
    void stampaBasi(int x, int y);
    void stampaQuadrato(int x, int y, GLfloat attivo);

};

class Gioco {
    //parametri finestra
    int larghezza_finestra;
    int altezza_finestra;
    int bpp;
    bool fullscreen;

    /* Flags to pass to SDL_SetVideoMode */
    unsigned videoFlags;

    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;

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
        bpp = BPP_FIN;

        fullscreen = false;
        stato = EDITOR_COSTRUISCI;
        alive = true;
        frame_ms = FRAMEMS;

        if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
            printf("ERRORE di inizializzazione SDL: %s.\n", SDL_GetError());
            exit(-1);
        }


        /* Fetch the video info */
        videoInfo = SDL_GetVideoInfo();

        if (!videoInfo) {
            fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
            exit(-1);
        }

        /* the flags to pass to SDL_SetVideoMode */
        videoFlags = SDL_OPENGL; /* Enable OpenGL in SDL */
        //videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
        videoFlags |= SDL_HWPALETTE; /* Store the palette in hardware */
        videoFlags |= SDL_RESIZABLE; /* Enable window resizing */
        //videoFlags |= SDL_GL_SWAP_CONTROL;

        /* This checks to see if surfaces can be stored in memory */
        if (videoInfo->hw_available)
            videoFlags |= SDL_HWSURFACE;
        else
            videoFlags |= SDL_SWSURFACE;

        /* This checks if hardware blits can be done */
        if (videoInfo->blit_hw)
            videoFlags |= SDL_HWACCEL;

        /* Sets up OpenGL double buffering */
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

        /* get a SDL surface */
        bpp = videoInfo->vfmt->BitsPerPixel;

        setWindowLA(LARGHEZZA_FIN, ALTEZZA_FIN);

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glEnable(GL_DEPTH_TEST); //questa andrà attivata

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        //se lo attivo sparisce anche le faccie laterali
        //glEnable(GL_CULL_FACE); //disattuva le faccie posteriori

        domino_editor.inizializzaEditor(this);
    }

    void loop() {
        Uint32 inizio, fine;
        int durata, aspetto;

        SDL_Event evento;
        while (SDL_PollEvent(&evento)) {
        }
        while (alive) {
            inizio = SDL_GetTicks();

            domino_editor.input();
            domino_editor.stato();
            domino_editor.video();
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

    void setWindowLA(int larghezza_finestra_aux, int altezza_finestra_aux) {
        larghezza_finestra = larghezza_finestra_aux;
        altezza_finestra = altezza_finestra_aux;
        screen = SDL_SetVideoMode(larghezza_finestra, altezza_finestra, bpp, videoFlags);
        if (!screen) {
            fprintf(stderr, "Could not get a surface after resize: %s\n", SDL_GetError());
            exit(-1);
        }
    }

    void setFullScreen() {
        fullscreen = true;
        SDL_WM_ToggleFullScreen(screen);
        //        videoFlags |= SDL_FULLSCREEN;
        //        setWindowLA(videoInfo->current_w, videoInfo->current_h);
    }

    void resetFullScreen() {
        fullscreen = false;
        SDL_WM_ToggleFullScreen(screen);
        //        videoFlags &= ~SDL_FULLSCREEN;
        //        setWindowLA(larghezza_finestra, altezza_finestra);
    }

    bool getFullScreen() {
        return fullscreen;
    }

    int getWindowL() {
        return larghezza_finestra;
    }

    int getWindowA() {
        return altezza_finestra;
    }

    int getScreenL() {
        return videoInfo->current_w;
    }

    int getScreenA() {
        return videoInfo->current_h;
    }
};

int main(int argc, char** argv) {
    Gioco domino;
    domino.loop();
    SDL_Quit();
    return (EXIT_SUCCESS);
}

int Editor::stato() {
    if (fabs(livello_editor.getGriglia().zoom - aux_griglia.zoom) >= 0.01) {
        livello_editor.setGrigliaXY(livello_editor.getGriglia().x + ((aux_griglia.x - livello_editor.getGriglia().x) / 10),
                livello_editor.getGriglia().y + ((aux_griglia.y - livello_editor.getGriglia().y) / 10));

        livello_editor.setGrigliaZoom(livello_editor.getGriglia().zoom + (aux_griglia.zoom - livello_editor.getGriglia().zoom) / 10);
    }
    return 1;
}

void Editor::stampaSuperficeBase() {
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorblue);
    glTranslatef(0.0, 0.0, POSIZIONE_SUPERFICE);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
    glVertex3f(num_x_colonne * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
    glVertex3f(num_x_colonne * ALTEZZA_PEZZO + ALTEZZA_PEZZO, num_y_righe * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
    glVertex3f(-ALTEZZA_PEZZO, num_y_righe * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
    glEnd();

    glPopMatrix();
}

void Editor::stampaPezzo(int x, int y) {

    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf + ((GLfloat) ALTEZZA_PEZZO / 2.0)-((GLfloat) SPESSORE_PEZZO / 2.0);
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coloryellow);
    glTranslatef(sposto_x, sposto_y, Z_PEZZO);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    }
    glEnd();
    glPopMatrix();
}

void Editor::stampaBasi(int x, int y) {


    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorgreen);
    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
    }
    glEnd();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
    }
    glEnd();
    glPopMatrix();
}

void Editor::stampaQuadrato(int x, int y, GLfloat attivo) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorgreen);
    glTranslatef(sposto_x, sposto_y, 0.0);
    glScalef(0.97, 0.97, 0.97);
    glTranslatef(ALTEZZA_PEZZO * 0.015, ALTEZZA_PEZZO * 0.015, ALTEZZA_PEZZO * 0.015);
    glColor4f(0.0f, 1.0f, 0.0f, attivo);
    glLineWidth(2.5);
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, -1.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 1.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, 1.0, -1.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 0.0, -1.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, 1.0, 1.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 0.0, 1.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 0.0, 1.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, -1.0, 1.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, -1.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
    //    /* double buffering! */
}

int Editor::video() {

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

    /*
     * GL_COLOR_BUFFER_BIT      Color buffers 		: Viene resa l’immagine (almeno 2, anche di piu’ per il rendering stereo.
     * GL_DEPTH_BUFFER_BIT      Depth buffer		: Usato per eliminare le parti nascoste.
     * GL_STENCIL_BUFFER_BIT    Stencil buffer 		: Usato per “ritagliare” aree dello schermo.
     * GL_ACCUM_BUFFER_BIT      Accumulation buffer	: Accumula i risultati per effetti speciali come  Motion Blur, simulare il fuoco, ombre, ...
     */


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
    if (getMousePosGrigliaXY(gioco->getWindowA())) {
        cubo_selezione[pos_x_griglia][pos_y_griglia] = 1;
    }

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

    glPopMatrix();
    SDL_GL_SwapBuffers();

    return 1;
}

int Editor::input() {
    SDL_PumpEvents();
    SDL_Event evento;
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
                        if (gioco->getFrames() > 1)
                            gioco->setFrames(gioco->getFrames() - 1);
                        break;
                    case SDLK_PAGEDOWN:
                        gioco->setFrames(gioco->getFrames() + 1);
                        break;
                    case SDLK_p:
                        SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
                        getMousePosGrigliaXY(gioco->getWindowA());
                        pos_x_iniziali = pos_x;
                        pos_y_iniziali = pos_y;
                        setProiezione(PROSPETTICA, gioco->getWindowL(), gioco->getWindowA());
                        getMousePosGrigliaXY(gioco->getWindowA());
                        livello_editor.setGrigliaXY(livello_editor.getGriglia().x + (pos_x - pos_x_iniziali), livello_editor.getGriglia().y + (pos_y - pos_y_iniziali));
                        break;
                    case SDLK_a:
                        SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
                        getMousePosGrigliaXY(gioco->getWindowA());
                        pos_x_iniziali = pos_x;
                        pos_y_iniziali = pos_y;
                        setProiezione(ASSIONOMETRICA, gioco->getWindowL(), gioco->getWindowA());
                        getMousePosGrigliaXY(gioco->getWindowA());
                        livello_editor.setGrigliaXY(livello_editor.getGriglia().x + (pos_x - pos_x_iniziali), livello_editor.getGriglia().y + (pos_y - pos_y_iniziali));
                        break;
                    case SDLK_f:
                        if (gioco->getFullScreen()) {
                            gioco->resetFullScreen();
                            //setProiezione(tipo_proiezione, gioco->getWindowA(), gioco->getWindowL());
                        } else {
                            gioco->setFullScreen();
                            //setProiezione(tipo_proiezione, gioco->getScreenA(), gioco->getScreenL());
                        }
                        break;
                    case SDLK_1:
                        posiziona_pezzi = true;
                        posiziona_basi = false;
                        posiziona_continua = 0;
                        break;
                    case SDLK_2:
                        posiziona_pezzi = false;
                        posiziona_basi = true;
                        posiziona_continua = 0;
                        break;
                    default:
                        break;

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                getMousePosGrigliaXY(gioco->getWindowA(), evento.button.x, evento.button.y);
                if (evento.button.button == SDL_BUTTON_LEFT) {
                    if (pos_griglia_ok) {
                        if (posiziona_pezzi) {
                            if (livello_editor.getPezzo(pos_x_griglia, pos_y_griglia).getAlive()) {
                                livello_editor.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(false);
                                posiziona_continua = -1;
                            } else {
                                livello_editor.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(true);
                                posiziona_continua = 1;
                            }
                        } else {
                            if (livello_editor.getBase(pos_x_griglia, pos_y_griglia).getAlive()) {
                                livello_editor.getBase(pos_x_griglia, pos_y_griglia).setAlive(false);
                                posiziona_continua = -1;
                            } else {
                                livello_editor.getBase(pos_x_griglia, pos_y_griglia).setAlive(true);
                                posiziona_continua = 1;
                            }
                        }
                    }
                }
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    pos_x_iniziali = pos_x;
                    pos_y_iniziali = pos_y;
                    aux_griglia.x = livello_editor.getGriglia().x;
                    aux_griglia.y = livello_editor.getGriglia().y;
                    aux_griglia.zoom = livello_editor.getGriglia().zoom;
                    bottone_destro = true;
                }
                if (!bottone_destro && evento.button.button == SDL_BUTTON_WHEELUP) {
                    GLfloat zoom = livello_editor.getGriglia().zoom;
                    if (zoom * DELTA_ZOOM < LIMITE_SUPERIORE_ZOOM) {
                        aux_griglia.zoom = zoom * DELTA_ZOOM;
                        aux_griglia.x = livello_editor.getGriglia().x + (1 - DELTA_ZOOM)*(pos_x - livello_editor.getGriglia().x);
                        aux_griglia.y = livello_editor.getGriglia().y + (1 - DELTA_ZOOM)*(pos_y - livello_editor.getGriglia().y);
                    } else {
                        aux_griglia.zoom = LIMITE_SUPERIORE_ZOOM;
                        aux_griglia.x = livello_editor.getGriglia().x + (1 - (GLfloat) LIMITE_SUPERIORE_ZOOM / zoom)*(pos_x - livello_editor.getGriglia().x);
                        aux_griglia.y = livello_editor.getGriglia().y + (1 - (GLfloat) LIMITE_SUPERIORE_ZOOM / zoom)*(pos_y - livello_editor.getGriglia().y);
                    }
                }
                if (!bottone_destro && evento.button.button == SDL_BUTTON_WHEELDOWN) {
                    GLfloat zoom = livello_editor.getGriglia().zoom;
                    if (zoom / DELTA_ZOOM > LIMITE_INFERIORE_ZOOM) {
                        aux_griglia.zoom = zoom / DELTA_ZOOM;
                        aux_griglia.x = livello_editor.getGriglia().x + ((DELTA_ZOOM - 1) / DELTA_ZOOM)*(pos_x - livello_editor.getGriglia().x);
                        aux_griglia.y = livello_editor.getGriglia().y + ((DELTA_ZOOM - 1) / DELTA_ZOOM)*(pos_y - livello_editor.getGriglia().y);
                    } else {
                        aux_griglia.zoom = LIMITE_INFERIORE_ZOOM;
                        aux_griglia.x = livello_editor.getGriglia().x + (((zoom / (GLfloat) LIMITE_INFERIORE_ZOOM) - 1) / (zoom / (GLfloat) LIMITE_INFERIORE_ZOOM))*(pos_x - livello_editor.getGriglia().x);
                        aux_griglia.y = livello_editor.getGriglia().y + (((zoom / (GLfloat) LIMITE_INFERIORE_ZOOM) - 1) / (zoom / (GLfloat) LIMITE_INFERIORE_ZOOM))*(pos_y - livello_editor.getGriglia().y);
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (getMousePosGrigliaXY(gioco->getWindowA(), evento.button.x, evento.button.y)) {
                    if (posiziona_continua == -1) {
                        if(posiziona_pezzi)
                            livello_editor.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(false);
                        else
                            livello_editor.getBase(pos_x_griglia, pos_y_griglia).setAlive(false);
                    }
                    if (posiziona_continua == 1) {
                        if(posiziona_pezzi)
                            livello_editor.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(true);
                        else
                            livello_editor.getBase(pos_x_griglia, pos_y_griglia).setAlive(true);
                    }
                }
                if (bottone_destro) {
                    livello_editor.setGrigliaXY(aux_griglia.x + (pos_x - pos_x_iniziali), aux_griglia.y + (pos_y - pos_y_iniziali));
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (evento.button.button == SDL_BUTTON_LEFT) {
                    posiziona_continua = 0;
                }
                if (evento.button.button == SDL_BUTTON_RIGHT) {
                    bottone_destro = false;
                }
                break;
            case SDL_VIDEORESIZE:
                gioco->setWindowLA(evento.resize.w, evento.resize.h);
                setProiezione(tipo_proiezione, evento.resize.w, evento.resize.h);
            default:
                break;
        }



    }
    return 1;
}