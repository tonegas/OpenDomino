/* 
 * File:   Partita.cpp
 * Author: tonegas
 * 
 * Created on 3 novembre 2009, 0.21
 */

#include "../include/Domino.h"

Partita::Partita(Gioco *gioco_aux, int num_y_righe_aux, int num_x_colonne_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux) {
    griglia_livello.setInPartita(true);
}

Partita::Partita(const Partita& orig) : Livello(orig) {
    griglia_livello.setInPartita(true);
}

Partita::Partita(const Livello& orig) : Livello(orig) {
    griglia_livello.setInPartita(true);
}

void Partita::mouseButtonDown(SDL_Event *evento) {
    if (evento->button.button == SDL_BUTTON_LEFT && telecamera_attuale->indice_griglia_ok) {
        telecamera_attuale->mouseSelezione(this,&griglia_livello);
        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                griglia_livello.setStato(x_pezzo_selezionato, y_pezzo_selezionato, CADE_DESTRA);
            }
        }
    }

}

void Partita::mouseMotion(SDL_Event *evento) {
    if (telecamera_attuale->indice_griglia_ok) {
        telecamera_attuale->mouseSelezione(this,&griglia_livello);
        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
            }
        }
    }
}

void Partita::attivaSelezioni() {
    if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
        if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
            griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
        }
    }
}

