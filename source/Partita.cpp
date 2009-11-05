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

Partita::Partita(const Livello& orig) : Livello(orig) {
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
                            ElementoAttivo *p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
                            if (p_aux_pezzo->getOccupato()) {
                                p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evento->button.button == SDL_BUTTON_LEFT && getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        mouseSelezione(gioco->getWindowA());
                        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
                            ElementoAttivo *p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
                            if (p_aux_pezzo->getOccupato()) {
                                griglia_livello.setStatoPezzo(x_pezzo_selezionato, y_pezzo_selezionato,CADE_DESTRA);
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
            ElementoAttivo *p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
            if (p_aux_pezzo->getOccupato()) {
                p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
            }
        }
    }
    return Livello::video();
}


//Partita::~Partita() {
//}

