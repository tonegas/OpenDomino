/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */


#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <math.h>

#include "include/appoggio/Evento.h"
#include "include/appoggio/Heap_Eventi.h"


using namespace std;


#define GAMERATE    60                  //aggiornamenti dello stato al secondo
#define GAMEMS      1000/GAMERATE       //millisecondi per aggiornare stato
#define FRAMERATE   50                  //frame per secondo massimi
#define FRAMEMS     1000/FRAMERATE      //millisecondi per frame


#define LARGHEZZA 4
#define ALTEZZA 8
#define SPESSORE 2

GLfloat rx = 0;
GLfloat ry = 0;
GLfloat rz = 0;
GLfloat startx = 0;
GLfloat starty = 0;
GLfloat jump = 0;

enum Stato_t {
    MENU,
    PARTITA,
    EDITOR
} Stato;

int statoThread(void *p);
int videoThread(void *p);
int inputThread(void *p);


Heap_Eventi Heap;

bool Alive;


SDL_Thread *input;
SDL_Thread *stato;

void prova(void *p) {
    cout << "EVENTO: " << (char *) p << '\n' << flush;
    //exit(1);
}

void gira(void *p) {
    double a=(int)p;
    jump += a/2;
}

void gameExit() {
    Alive = false;
}

const GLfloat cavalier[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    -0.5, -0.5, 1, 0,
    0, 0, 0, 1
};

void stampaPezzo();

int main(int argc, char** argv) {
    Stato = PARTITA;
    Alive = true;

    if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
        printf("Could not initialize SDL: %s.\n",
                SDL_GetError()); /* stampa dell’errore */
        exit(-1);
    }

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE);

    Heap.inserisciEvento(prova, (void*) "start", 0);
    Heap.inserisciEvento(gira, (void*) 90, 10000);
    Heap.inserisciEventoPeriodico(gira, (void*)1, 10, 1);

    input = SDL_CreateThread(inputThread, NULL);
    stato = SDL_CreateThread(statoThread, NULL);

    videoThread(NULL);
    //    SDL_Flip(screen);

    SDL_WaitThread(input, NULL);
    SDL_WaitThread(stato, NULL);
    SDL_Quit();
    return (EXIT_SUCCESS);
}

int statoThread(void *p) {
    Uint32 tempo;
    int aspetto;
    Evento evento;
    while (Alive) {
        evento = Heap.estraiEvento(); //bloccante fin che non c'è un evento attende dentro la funzione
        tempo = SDL_GetTicks();
        aspetto = evento.getQuando() - tempo;
        if (aspetto > 0)
            SDL_Delay(aspetto);
        evento.esegui();
    }
    return 1;
}

void stampaPezzo(GLfloat ang) {
    /* clear screen */

    glPushMatrix();

    /* affine transformations */
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);

    /* orientation vectors */
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();

    /* base quad */
    // 		glColor3f(0.2f,0.2f,0.2f);
    // 		glBegin(GL_QUADS );
    // 			glVertex3f(-10,-5,-10);
    // 			glVertex3f(+10,-5,-10);
    // 			glVertex3f(+10,-5,+10);
    // 			glVertex3f(-10,-5,+10);
    // 		glEnd();

    /* wire cube */
    glPushMatrix();
    glRotatef(jump + ang, 0.0, 0.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-SPESSORE, 0.0, 0.0);
    glVertex3f(-SPESSORE, ALTEZZA, 0.0);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, LARGHEZZA);
    glVertex3f(-SPESSORE, 0.0, LARGHEZZA);
    glVertex3f(-SPESSORE, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, 0.0, LARGHEZZA);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-SPESSORE, 0.0, 0.0);
    glVertex3f(-SPESSORE, 0.0, LARGHEZZA);
    glVertex3f(0.0, 0.0, LARGHEZZA);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glVertex3f(-SPESSORE, ALTEZZA, 0.0);
    glVertex3f(-SPESSORE, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, ALTEZZA, LARGHEZZA);
    glVertex3f(0.0, ALTEZZA, 0.0);
    glEnd();
    // 			glColor3f(0.0f,1.0f,1.0f);
    // 			glBegin(GL_QUADS );
    // 				glVertex3f(0,-5,-5);
    // 				glVertex3f(+1,-5,-5);
    // 				glVertex3f(+1,-5,+5);
    // 				glVertex3f(0,-5,+5);
    // 			glEnd();
    // 			glBegin(GL_QUADS );
    // 				glVertex3f(+1,-5,-5);
    // 				glVertex3f(+1,-5,+5);
    // 				glVertex3f(+1,+5,+5);
    // 				glVertex3f(+1,+5,-5);
    // 			glEnd();
    // 			glBegin(GL_QUADS );
    // 				glVertex3f(+1,-5,+5);
    // 				glVertex3f(+1,+5,+5);
    // 				glVertex3f(0,+5,+5);
    // 				glVertex3f(0,-5,+5);
    // 			glEnd();
    // 			glBegin(GL_QUADS );
    // 				glVertex3f(+5,+5,+5);
    // 				glVertex3f(-5,+5,+5);
    // 				glVertex3f(-5,+5,-5);
    // 				glVertex3f(+5,+5,-5);
    // 			glEnd();
    glPopMatrix();

    glPopMatrix();
    /* double buffering! */
}

int videoThread(void *p) {

    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 30, 0, 30, -30, 60);
    glMultMatrixf(cavalier);

    //   gluPerspective
    //   (
    // 		 40.0,  /* field of view in degree */
    // 		 1.0,   /* aspect ratio */
    // 		 20.0, /* Z near */
    // 		100.0 /* Z far */
    //   );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0.0, 0.0, 30.0, /* eye  */
            0.0, 0.0, 0.0, /* center  */
            0.0, 1.0, 0.0); /* up is in positive Y direction */

    Uint32 inizio, fine;
    int durata, aspetto;

    while (Alive) {
        inizio = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //for (int i = 0; i < 90; i++)stampaPezzo(i * 2);
        stampaPezzo(0);

        SDL_GL_SwapBuffers();
        fine = SDL_GetTicks();
        durata = fine - inizio;
        aspetto = FRAMEMS - durata;
        if (aspetto > 0)
            SDL_Delay(aspetto);
    }
    
    return 1;
}

void statusPartita(SDL_Event *evento) {
    switch (evento->type) {
        case SDL_KEYDOWN:
            SDL_KeyboardEvent *aux_t;
            aux_t = (SDL_KeyboardEvent*) evento;
            Heap.inserisciEvento(prova, (void*) "tasto premuto", SDL_GetTicks());
            switch (aux_t->keysym.sym) {
                case SDLK_q:
                    break;
                case SDLK_a:
                    rx--;
                    break;
                case SDLK_w:
                    ry++;
                    break;
                case SDLK_s:
                    ry--;
                    break;
                case SDLK_e:
                    rz++;
                    break;
                case SDLK_d:
                    rz--;
                    break;
                default:
                    break;

            }
            break;
        case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEMOTION:
            SDL_MouseButtonEvent *aux_m;
            aux_m = (SDL_MouseButtonEvent*) evento;
            Heap.inserisciEvento(prova, (void*) "mouse premuto", SDL_GetTicks());
            if (aux_m->button == SDL_BUTTON_LEFT) {
                ry = ry + (aux_m->x - startx);
                rx = rx + (aux_m->y - starty);
                startx = aux_m->x;
                starty = aux_m->y;
            }
            break;
        default:
            break;
    }
}

int inputThread(void *p) {
    SDL_Event evento;
    while (Alive && SDL_WaitEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            gameExit();
        }
        switch (Stato) {
            case MENU:
                break;
            case PARTITA:
                statusPartita(&evento);
                break;
            case EDITOR:
                break;
        }
    }
    return 1;
}