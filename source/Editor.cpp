/* 
 * File:   Editor.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.37
 */

#include "../include/Domino.h"
//#include "../include/Editor.h"
//#include "../include/Partita.h"
//#include "../include/Gioco.h"

using namespace std;

Editor::Editor(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux, FRAMERATE) {
//    test_partita_allocata = false;
//    test = NULL;
    tipo_proiezione = ASSIONOMETRICA;
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    azione_continua = NESSUNA_AZIONE;
    entrambi = false;

    //    cubo_selezione = new GLfloat*[num_x_colonne];
    //    for (int i = 0; i < num_x_colonne; i++)
    //        cubo_selezione[i] = new GLfloat[num_y_righe];
    //    for (int i = 0; i < num_x_colonne; i++)
    //        for (int j = 0; j < num_y_righe; j++)
    //            cubo_selezione[i][j] = 0;
}

Editor::~Editor() {
//    if (test_partita_allocata)
//        delete test;
    //    for (int i = 0; i < num_y_righe; i++)
    //        delete []cubo_selezione[i];
    //    delete []cubo_selezione;
}

//int Editor::aggiornaStato() {
//    if (gioco->getStato() == EDITOR_TEST) {
//        return test->aggiornaStato();
//    } else {
//        return aggiornaStatoEditor();
//    }
//}

//int Editor::aggiornaStatoEditor() {
//    return Livello::aggiornaStato();
//}

//int Editor::video() {
//    if (gioco->getStato() == EDITOR_TEST) {
//        return test->video();
//    } else {
//        return videoEditor();
//    }
//}

void Editor::attivaSelezioni() {
    if (caratteristiche_selezione == DAVANTI_PEZZO && azione_continua != POSIZIONA_BASI) {
        griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
    } else if (caratteristiche_selezione == DAVANTI_BASE && azione_continua != POSIZIONA_PEZZI) {
        griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
    }
}

//int Editor::gestisciInput(SDL_Event *evento) {
//    if (gioco->getStato() == EDITOR_TEST) {
//        return test->gestisciInput(evento);
//    } else {
//        return gestisciInputEditor(evento);
//    }
//}

void Editor::mouseButtonDown(SDL_Event *evento) {
    if (evento->button.button == SDL_BUTTON_LEFT && pos_griglia_ok) {
        mouseSelezione(gioco->getWindowA());
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

void Editor::mouseMotion(SDL_Event *evento) {
    if (pos_griglia_ok) {
        mouseSelezione(gioco->getWindowA());
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

//void Editor::keyDownF5(SDL_Event *evento) {
//    if (gioco->getStato() == EDITOR_TEST) {
//        gioco->setStato(EDITOR_COSTRUISCI);
//    } else {
//        gioco->setStato(EDITOR_TEST);
//    }
//}

void Editor::mouseButtonUp(SDL_Event *evento) {
    if (evento->button.button == SDL_BUTTON_LEFT) {
        azione_continua = NESSUNA_AZIONE;
    }
}

//int Editor::gestisciInputEditor(SDL_Event *evento) {
//    SDL_PumpEvents();
//    while (SDL_PollEvent(evento)) {
//        if (Livello::gestisciInput(evento)) {
//            switch (evento->type) {
//                case SDL_KEYDOWN:
//                    switch (evento->key.keysym.sym) {
//                        case SDLK_1:
//                            break;
//                        case SDLK_2:
//                            break;
//                        case SDLK_F5:
//                            gioco->setStato(EDITOR_TEST);
//                            if (test_partita_allocata) {
//                                delete test;
//                                test = new Partita(*this);
//                            } else {
//                                test_partita_allocata = true;
//                                test = new Partita(*this);
//                            }
//                            break;
//                        default:
//                            break;
//
//                    }
//                    break;
//                case SDL_MOUSEBUTTONDOWN:
//                    if (evento->button.button == SDL_BUTTON_LEFT && getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
//                        mouseSelezione(gioco->getWindowA());
//                        if (caratteristiche_selezione == DAVANTI_PEZZO) {
//                            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
//                                griglia_livello.eliminaElemento(x_pezzo_selezionato, y_pezzo_selezionato);
//                                azione_continua = ELIMINA_PEZZI;
//                            } else {
//                                griglia_livello.creaElemento(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
//                                azione_continua = POSIZIONA_PEZZI;
//                            }
//                            griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
//                        } else if (caratteristiche_selezione == DAVANTI_BASE) {
//                            if (griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)) {
//                                griglia_livello.eliminaElemento(x_base_selezionata, y_base_selezionata);
//                                azione_continua = ELIMINA_BASI;
//                            } else {
//                                griglia_livello.creaElemento(x_base_selezionata, y_base_selezionata, ELEM_BASE);
//                                azione_continua = POSIZIONA_BASI;
//                            }
//                            griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
//                        }
//                    }
//                    break;
//                case SDL_MOUSEMOTION:
//                    if (getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
//                        mouseSelezione(gioco->getWindowA());
//                        switch (azione_continua) {
//                            case POSIZIONA_PEZZI:
//                                if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi) {
//                                    if (!griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato))
//                                        griglia_livello.creaElemento(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
//                                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
//                                }
//                                break;
//                            case POSIZIONA_BASI:
//                                if (caratteristiche_selezione == DAVANTI_BASE || entrambi) {
//                                    if (!griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata))
//                                        griglia_livello.creaElemento(x_base_selezionata, y_base_selezionata, ELEM_BASE);
//                                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
//                                }
//                                break;
//                            case ELIMINA_PEZZI:
//                                if ((caratteristiche_selezione == DAVANTI_PEZZO || entrambi) && griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)
//                                        && griglia_livello.getTipo(x_pezzo_selezionato, y_pezzo_selezionato) == ELEM_PEZZO) {
//                                    griglia_livello.eliminaElemento(x_pezzo_selezionato, y_pezzo_selezionato);
//                                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
//                                }
//                                caratteristiche_selezione = NIENTE;
//                                break;
//                            case ELIMINA_BASI:
//                                if ((caratteristiche_selezione == DAVANTI_BASE || entrambi) && griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)
//                                        && griglia_livello.getTipo(x_base_selezionata, y_base_selezionata) == ELEM_BASE) {
//                                    griglia_livello.eliminaElemento(x_base_selezionata, y_base_selezionata);
//                                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
//                                }
//                                caratteristiche_selezione = NIENTE;
//                                break;
//                            default:
//                                if (caratteristiche_selezione == DAVANTI_PEZZO) {
//                                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato, ELEM_PEZZO);
//                                }
//                                if (caratteristiche_selezione == DAVANTI_BASE) {
//                                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata, ELEM_BASE);
//                                }
//                                break;
//                        }
//                    }
//                    break;
//                case SDL_MOUSEBUTTONUP:
//                    if (evento->button.button == SDL_BUTTON_LEFT) {
//                        azione_continua = NESSUNA_AZIONE;
//                    }
//                    break;
//                default:
//                    break;
//            }
//        }
//    }
//    return 1;
//}