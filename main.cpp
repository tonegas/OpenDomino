/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include <SDL/SDL.h>
#include <stdlib.h>

#define GAMERATE    60                  //aggiornamenti dello stato al secondo
#define GAMEMS      1000/GAMERATE       //millisecondi per aggiornare stato
#define FRAMERATE   50                  //frame per secondo massimi
#define FRAMEMS     1000/FRAMERATE      //millisecondi per frame

enum Stato_t {
    MENU,
    PARTITA,
    EDITOR
} Stato;

Uint32 statoThread(Uint32 gamespeed, void *p);
int videoThread(void *p);
int inputThread(void *p);


int main(int argc, char** argv) {
    SDL_TimerID timerStato;
    SDL_Thread *input = SDL_CreateThread(inputThread, NULL);
    SDL_Thread *video = SDL_CreateThread(videoThread, NULL);
    timerStato = SDL_AddTimer((Uint32)GAMEMS, statoThread, NULL);

    SDL_WaitThread(video, NULL);
    SDL_WaitThread(input, NULL);
    SDL_RemoveTimer(timerStato);
    return (EXIT_SUCCESS);
}

Uint32 statoThread(Uint32 gamems, void *p) {
    return 1;
}

int videoThread(void *p) {
    Uint32 inizio,fine,durata,aspetto;
    while(true){
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