/* 
 * File:   Editor.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.37
 */

#include "../include/Domino.h"

Editor::Editor(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux) {
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    azione_continua = NESSUNA_AZIONE;
    //esempio configurazione telecamera per livello
//    PosTeleAssio aux_tele(100,213,2);
//    tele_assio = aux_tele;
    //---------------------------------
}

Editor::~Editor() {

}


void Editor::attivaSelezioni() {
    if (caratteristiche_selezione == DAVANTI_PEZZO && azione_continua != POSIZIONA_BASI) {
        griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
    } else if (caratteristiche_selezione == DAVANTI_BASE && azione_continua != POSIZIONA_PEZZI) {
        griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
    }
}

void Editor::mouseButtonDown(SDL_Event *evento) {
    if (evento->button.button == SDL_BUTTON_LEFT && telecamera_attuale->indice_griglia_ok) {
        telecamera_attuale->mouseSelezione(this,&griglia_livello);
        //??????????????
        //mouseSelezione(gioco->getWindowA());
        //?????????????
        if (caratteristiche_selezione == DAVANTI_PEZZO) {
            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                griglia_livello.eliminaElemento(x_pezzo_selezionato, y_pezzo_selezionato);
                azione_continua = ELIMINA_PEZZI;
            } else {
                griglia_livello.creaElemento(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
                azione_continua = POSIZIONA_PEZZI;
            }
            griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
        } else if (caratteristiche_selezione == DAVANTI_BASE) {
            if (griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)) {
                griglia_livello.eliminaElemento(x_base_selezionata, y_base_selezionata);
                azione_continua = ELIMINA_BASI;
            } else {
                griglia_livello.creaElemento(x_base_selezionata, y_base_selezionata, ELEM_BASE);
                azione_continua = POSIZIONA_BASI;
            }
            griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
        }
    }
}

void Editor::mouseMotion() {
    if (telecamera_attuale->indice_griglia_ok) {
        telecamera_attuale->mouseSelezione(this,&griglia_livello);
        //??????????????
        //mouseSelezione(gioco->getWindowA());
        //??????????????
        switch (azione_continua) {
            case POSIZIONA_PEZZI:
                if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
                    if (!griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato))
                        griglia_livello.creaElemento(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
                }
                break;
            case POSIZIONA_BASI:
                if (caratteristiche_selezione == DAVANTI_BASE || entrambi) {
                    if (!griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata))
                        griglia_livello.creaElemento(x_base_selezionata, y_base_selezionata, ELEM_BASE);
                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
                }
                break;
            case ELIMINA_PEZZI:
                if ((caratteristiche_selezione == DAVANTI_PEZZO || entrambi) && griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)
                        && griglia_livello.getTipo(x_pezzo_selezionato, y_pezzo_selezionato) == ELEM_PEZZO) {
                    griglia_livello.eliminaElemento(x_pezzo_selezionato, y_pezzo_selezionato);
                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
                }
                caratteristiche_selezione = NIENTE;
                break;
            case ELIMINA_BASI:
                if ((caratteristiche_selezione == DAVANTI_BASE || entrambi) && griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)
                        && griglia_livello.getTipo(x_base_selezionata, y_base_selezionata) == ELEM_BASE) {
                    griglia_livello.eliminaElemento(x_base_selezionata, y_base_selezionata);
                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
                }
                caratteristiche_selezione = NIENTE;
                break;
            default:
                if (caratteristiche_selezione == DAVANTI_PEZZO) {
                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
                }
                if (caratteristiche_selezione == DAVANTI_BASE) {
                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
                }
                break;
        }
    }
}

void Editor::mouseButtonUp(SDL_Event *evento) {
    if (evento->button.button == SDL_BUTTON_LEFT) {
        azione_continua = NESSUNA_AZIONE;
    }
}