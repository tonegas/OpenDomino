/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include <SDL/SDL.h>
#include <stdlib.h>
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
public:
    Uint32 quando;
    static bool comp(const eventi &elem1,const eventi &elem2){
        if(elem1.quando<elem2.quando){
            return true;
        }else{
            return false;
        }
    }
    Uint32 getQuando(){
        return quando;
    }
    void esegui(){
        fn(param);
    }
};



int main(int argc, char** argv) {
    SDL_Thread *input = SDL_CreateThread(inputThread, NULL);
    SDL_Thread *video = SDL_CreateThread(videoThread, NULL);
    SDL_Thread *stato = SDL_CreateThread(statoThread, NULL);

    SDL_WaitThread(video, NULL);
    SDL_WaitThread(input, NULL);
    SDL_WaitThread(stato, NULL);
    return (EXIT_SUCCESS);
}

int statoThread(void *p) {
    Uint32 tempo, aspetto;
    vector<eventi> heap_eventi;
    eventi evento;
    while (true) {
        if (!heap_eventi.empty()) {
            evento = heap_eventi.front();
            pop_heap(heap_eventi.begin(), heap_eventi.end(),eventi::comp);
            heap_eventi.pop_back();

            /*   inserire elemento
             *   v.push_back(99); push_heap (v.begin(),v.end());
             */
            
            tempo = SDL_GetTicks();
            aspetto = evento.getQuando() - tempo;
            if (aspetto > 0)
                SDL_Delay(aspetto);
            evento.esegui();
        }
    }
    return 1;
}

int videoThread(void *p) {
    Uint32 inizio, fine, durata, aspetto;
    while (true) {
        inizio = SDL_GetTicks();
        //codice
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
            //        case SDL_KEYDOWN:
            //            SDL_KeyboardEvent *ke = (SDL_KeyboardEvent *) evento;
    }
}

int inputThread(void *p) {
    SDL_Event *evento;
    while (SDL_WaitEvent(evento)) {
        switch (Stato) {
            case MENU:
                break;
            case PARTITA:
                statusPartita(evento);
                break;
            case EDITOR:
                break;
        }
        free(evento);
    }
    return 1;
}