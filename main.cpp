/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include <SDL/SDL.h>
#include <stdlib.h>

typedef enum {
    MENU,
    PARTITA,
    EDITOR
} Stato_t;

/*
 * 
 */
int main(int argc, char** argv) {
    SDL_Event *evento;
    while (SDL_WaitEvent(evento)) {
        switch (Stato_t) {
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
    return (EXIT_SUCCESS);
}

void statusPartita(SDL_Event *evento) {
    switch (evento->type) {
        case SDL_KEYDOWN:
            SDL_KeyboardEvent *ke = (SDL_KeyboardEvent *) evento;
    }
}