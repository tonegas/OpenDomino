/* 
 * File:   Partita.cpp
 * Author: tonegas
 * 
 * Created on 3 novembre 2009, 0.21
 */

#include "../include/Domino.h"
//#include "../include/Partita.h"
//#include "../include/Gioco.h"

using namespace std;

Partita::Partita(Gioco *gioco_aux, int num_y_righe_aux, int num_x_colonne_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux, FRAMERATE) {
    griglia_livello.setInPartita(true);
}

Partita::Partita(const Partita& orig) : Livello(orig) {
    griglia_livello.setInPartita(true);
}

Partita::Partita(const Livello& orig) : Livello(orig) {
    griglia_livello.setInPartita(true);
}

int Partita::aggiornaStato() {
    return Livello::aggiornaStato();
}

int Partita::gestisciInput(SDL_Event * evento) {
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
                case SDL_MOUSEMOTION:
                    if (getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        mouseSelezione(gioco->getWindowA());
                        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
                            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                                griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evento->button.button == SDL_BUTTON_LEFT && getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        mouseSelezione(gioco->getWindowA());
                        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
                            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                                griglia_livello.setStato(x_pezzo_selezionato, y_pezzo_selezionato, CADE_DESTRA);
                            } else {
                                cout << "NONOCCUPATO" << flush;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}

int Partita::video() {
    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
    if (getMousePosGrigliaXY(gioco->getWindowA())) {
        mouseSelezione(gioco->getWindowA());
        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
            }
        }
    }

    return Livello::video();
}

//Partita::~Partita() {
//}

