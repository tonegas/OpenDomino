/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include <SDL/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


#define GAMERATE    60                  //aggiornamenti dello stato al secondo
#define GAMEMS      1000/GAMERATE       //millisecondi per aggiornare stato
#define FRAMERATE   50                  //frame per secondo massimi
#define FRAMEMS     1000/FRAMERATE      //millisecondi per frame

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
SDL_cond *nuovo_evento_cond = SDL_CreateCond();
SDL_mutex *nuovo_evento_mutex = SDL_CreateMutex();

void prova(void *p) {
    cout << "prova vai " << (char *) p << '\n' << flush;
    //exit(1);
}

int main(int argc, char** argv) {
    Stato = PARTITA;

    eventi pp(prova, (void*) "inizio", 2000);
    heap_eventi.push_back(pp);
    push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);
    eventi pp1(prova, (void*) "inizio_2", 1000);
    heap_eventi.push_back(pp1);
    push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);


    if ((SDL_Init(SDL_INIT_EVERYTHING)==-1))
    {
       printf("Could not initialize SDL: %s.\n",
      SDL_GetError()); /* stampa dell’errore */
       exit(-1);
    }

    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    SDL_Thread *input = SDL_CreateThread(inputThread, NULL);
    SDL_Thread *video = SDL_CreateThread(videoThread, NULL);
    SDL_Thread *stato = SDL_CreateThread(statoThread, NULL);


    SDL_WaitThread(video, NULL);
    SDL_WaitThread(input, NULL);
    SDL_WaitThread(stato, NULL);

//    SDL_Flip(screen);

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

int videoThread(void *p) {
    Uint32 inizio, fine;
    int durata, aspetto;
    while (true) {
        inizio = SDL_GetTicks();


        SDL_Delay(1000);
        eventi pp6(prova, (void*) "video", SDL_GetTicks());
        heap_eventi.push_back(pp6);
        push_heap(heap_eventi.begin(), heap_eventi.end(), eventi::comp);
        SDL_CondSignal(nuovo_evento_cond);

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
              ke = (SDL_KeyboardEvent*)evento;
              if(SDLK_SPACE == ke->keysym.sym){
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