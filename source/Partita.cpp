/* 
 * File:   Partita.cpp
 * Author: tonegas
 * 
 * Created on 3 novembre 2009, 0.21
 */

#include "../include/Partita.h"
#include "../include/Gioco.h"

using namespace std;

Partita::Partita(Gioco *gioco_aux, int num_y_righe_aux, int num_x_colonne_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux, FRAMERATE) {
}

Partita::Partita(const Partita& orig) : Livello(orig) {
}

int Partita::aggiornaStato() {
    Livello::aggiornaStato();
    return 1;
}

int Partita::gestisciInput(SDL_Event *evento) {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        if (Livello::gestisciInput(evento)) {
            switch (evento->type) {
                case SDL_KEYDOWN:
                    switch (evento->key.keysym.sym) {
                        case SDLK_F6:
                            gioco->setStato(EDITOR_COSTRUISCI);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}


    //Partita::~Partita() {
    //}

