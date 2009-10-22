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
#include <algorithm>
#include <vector>
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
float jump = 0.0;

enum Stato_t {
    MENU,
    PARTITA,
    EDITOR
} Stato;

int statoThread(void *p);
int videoThread(void *p);
int inputThread(void *p);

class eventi {
    void (*fn)(void*);
    void *param;
    Uint32 quando;
public:

    eventi() {
    }

    eventi(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux) {
        fn = fn_aux;
        param = param_aux;
        quando = quando_aux;
    }

    eventi(const eventi &evento_aux) {
        fn = evento_aux.fn;
        param = evento_aux.param;
        quando = evento_aux.quando;
    }

    static bool comp(const eventi &elem1, const eventi &elem2) {
        if (elem1.quando > elem2.quando) {
            return true;
        } else {
            return false;
        }
    }

    Uint32 getQuando() {
        return quando;
    }

    void esegui() {
        fn(param);
    }
};

vector<eventi> heap_eventi;
SDL_cond *nuovo_evento_cond;
SDL_mutex *nuovo_evento_mutex;

SDL_Thread *input;
SDL_Thread *video;
SDL_Thread *stato;

SDL_Surface *screen;

void prova(void *p) {
    cout << "prova vai " << (char *) p << '\n' << flush;
    //exit(1);
}

void gameExit() {
    SDL_KillThread(video);
    SDL_KillThread(input);
    SDL_KillThread(stato);
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

    eventi pp(prova, (void*) "inizio", 2000);
    heap_eventi.push_back(pp);
    push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);
    eventi pp1(prova, (void*) "inizio_2", 1000);
    heap_eventi.push_back(pp1);
    push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);


    if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
        printf("Could not initialize SDL: %s.\n",
                SDL_GetError()); /* stampa dell’errore */
        exit(-1);
    }

    nuovo_evento_cond = SDL_CreateCond();
    nuovo_evento_mutex = SDL_CreateMutex();


//    stampaPezzo();


    input = SDL_CreateThread(inputThread, NULL);
    video = SDL_CreateThread(videoThread, NULL);
    stato = SDL_CreateThread(statoThread, NULL);

    //    SDL_Flip(screen);

    SDL_WaitThread(video, NULL);
    SDL_WaitThread(input, NULL);
    SDL_WaitThread(stato, NULL);
    SDL_Quit();
    return (EXIT_SUCCESS);
}

int statoThread(void *p) {
    Uint32 tempo;
    int aspetto;
    eventi evento;
    SDL_mutexP(nuovo_evento_mutex);
    while (true) {
        if (!heap_eventi.empty()) {
            evento = heap_eventi.front();
            pop_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);
            heap_eventi.pop_back();

            /*   inserire elemento
             *   v.push_back(99); push_heap (v.begin(),v.end());
             */

            tempo = SDL_GetTicks();
            aspetto = evento.getQuando() - tempo;
            if (aspetto > 0)
                SDL_Delay(aspetto);
            evento.esegui();
        } else {
            SDL_CondWait(nuovo_evento_cond, nuovo_evento_mutex);
        }
    }
    return 1;
}

void stampaPezzo() {
    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    glRotatef(-2 * jump, 0.0, 0.0, 1.0);
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
    SDL_GL_SwapBuffers();
    /* double buffering! */
}

int videoThread(void *p) {

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

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
    while (true) {
        inizio = SDL_GetTicks();

        SDL_Delay(5000);
        eventi pp6(prova, (void*) "video", SDL_GetTicks());
        heap_eventi.push_back(pp6);
        push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);
        SDL_CondSignal(nuovo_evento_cond);
        stampaPezzo();

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
            SDL_KeyboardEvent *ke;
            ke = (SDL_KeyboardEvent*) evento;
            if (SDLK_SPACE == ke->keysym.sym) {
                eventi pp6(prova, (void*) "tasto", SDL_GetTicks());
                heap_eventi.push_back(pp6);
                push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);
                SDL_CondSignal(nuovo_evento_cond);
            }
            break;
        default:
            break;
    }
}

int inputThread(void *p) {
    SDL_Event evento;
    while (SDL_WaitEvent(&evento)) {
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
        //free(evento);
    }
    return 1;
}