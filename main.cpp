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
#include <math.h>
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

class Evento {
    void (*fn)(void*);
    void *param;
    bool rip;
    Uint32 quando;
    Uint32 intervallo;

public:

    Evento() {
    }

    Evento(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux) {
        fn = fn_aux;
        param = param_aux;
        quando = quando_aux;
        rip = 0;
    }

    Evento(void (*fn_aux)(void*), void *param_aux, Uint32 intervallo_aux, bool rip_aux) {
        fn = fn_aux;
        param = param_aux;
        intervallo = intervallo_aux;
        quando = SDL_GetTicks() + intervallo_aux;
        rip = rip_aux;
    }

    Evento(const Evento &evento_aux) {
        fn = evento_aux.fn;
        param = evento_aux.param;
        quando = evento_aux.quando;
        intervallo = evento_aux.intervallo;
        rip = evento_aux.rip;
    }

    static bool comp(const Evento &elem1, const Evento &elem2) {
        if (elem1.quando > elem2.quando) {
            return true;
        } else {
            return false;
        }
    }

    bool getRip() {
        return rip;
    }

    Uint32 getIntervallo() {
        return intervallo;
    }

    Uint32 getQuando() {
        return quando;
    }

    void setQuando(Uint32 quando_aux) {
        quando = quando_aux;
    }

    void esegui() {
        fn(param);
    }
};

class Heap_eventi {
    vector<Evento> Heap;
    SDL_cond *nuovo_evento_cond;
    SDL_mutex *nuovo_evento_mutex;

public:

    Heap_eventi() {
        nuovo_evento_cond = SDL_CreateCond();
        nuovo_evento_mutex = SDL_CreateMutex();
    }

    void inserisciEvento(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux) {
        Evento aux(fn_aux, param_aux, quando_aux);
        SDL_mutexP(nuovo_evento_mutex);
        Heap.push_back(aux);
        push_heap(Heap.begin(), Heap.end(), Evento::comp);
        SDL_CondSignal(nuovo_evento_cond);
        SDL_mutexV(nuovo_evento_mutex);
    }

    void inserisciEventoPeriodico(void (*fn_aux)(void*), void *param_aux, Uint32 intervallo_aux, bool rip_aux) {
        Evento aux(fn_aux, param_aux, intervallo_aux, rip_aux);
        SDL_mutexP(nuovo_evento_mutex);
        Heap.push_back(aux);
        push_heap(Heap.begin(), Heap.end(), Evento::comp);
        SDL_CondSignal(nuovo_evento_cond);
        SDL_mutexV(nuovo_evento_mutex);
    }

    Evento estraiEvento() {
        SDL_mutexP(nuovo_evento_mutex);
        if (Heap.empty()) {
            SDL_CondWait(nuovo_evento_cond, nuovo_evento_mutex);
        }
        Evento evento = Heap.front();
        pop_heap(Heap.begin(), Heap.end(), Evento::comp);
        Heap.pop_back();
        if (evento.getRip() == 1) {
            evento.setQuando(SDL_GetTicks() + evento.getIntervallo());
            Heap.push_back(evento);
            push_heap(Heap.begin(), Heap.end(), Evento::comp);
            SDL_CondSignal(nuovo_evento_cond);
        }
        SDL_mutexV(nuovo_evento_mutex);
        return evento;
    }

    void controlloHeap() {
        for (unsigned i = 0; i < Heap.size(); i++) cout << " " << Heap[i].getQuando() << flush;
    }

    bool empty() {
        return Heap.empty();
    }



};

Heap_eventi Heap;

bool Alive;


SDL_Thread *input;
SDL_Thread *video;
SDL_Thread *stato;

void prova(void *p) {
    cout << "EVENTO: " << (char *) p << '\n' << flush;
    //exit(1);
}

void gira(void *p) {
    jump += (int) p;
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

    Heap.inserisciEvento(prova, (void*) "start", 0);
    Heap.inserisciEvento(gira, (void*) 90, 10000);
    Heap.inserisciEventoPeriodico(gira, (void*) 1, 10, 1);

    video = SDL_CreateThread(videoThread, NULL);
    SDL_Delay(1000);
    input = SDL_CreateThread(inputThread, NULL);
    stato = SDL_CreateThread(statoThread, NULL);

    //    SDL_Flip(screen);

    SDL_WaitThread(input, NULL);
    SDL_WaitThread(video, NULL);
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

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER);


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

        for (int i = 0; i < 90; i++)stampaPezzo(i * 2);

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
                    rx++;
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