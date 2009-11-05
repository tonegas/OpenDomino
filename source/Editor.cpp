/* 
 * File:   Editor.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.37
 */

#include "../include/Editor.h"
#include "../include/Partita.h"
#include "../include/Gioco.h"

using namespace std;

Editor::Editor(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux, FRAMERATE) {
    test_partita_allocata = false;
    test = NULL;
    tipo_proiezione = ASSIONOMETRICA;
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    posiziona_pezzi = true;
    azione_continua = 0;
    entrambi = false;

    //    cubo_selezione = new GLfloat*[num_x_colonne];
    //    for (int i = 0; i < num_x_colonne; i++)
    //        cubo_selezione[i] = new GLfloat[num_y_righe];
    //    for (int i = 0; i < num_x_colonne; i++)
    //        for (int j = 0; j < num_y_righe; j++)
    //            cubo_selezione[i][j] = 0;
}

Editor::~Editor() {
    if (test_partita_allocata)
        delete test;
    //    for (int i = 0; i < num_y_righe; i++)
    //        delete []cubo_selezione[i];
    //    delete []cubo_selezione;
}

void Editor::stampaQuadrato(int x, int y, GLfloat attivo) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glDisable(GL_LIGHTING);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorgreen);
    glTranslatef(sposto_x, sposto_y, 0.0);
    glScalef(0.97, 0.97, 0.97);
    glTranslatef(ALTEZZA_PEZZO * 0.015, ALTEZZA_PEZZO * 0.015, ALTEZZA_PEZZO * 0.015);
    glColor4f(0.0f, 1.0f, 0.0f, attivo);
    glLineWidth(2.5);
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, -1.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 1.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, 1.0, -1.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 0.0, -1.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, 1.0, 1.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 0.0, 1.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 0.0, 1.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, -1.0, 1.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, -1.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
    //    /* double buffering! */
}

int Editor::aggiornaStato() {
    if (gioco->getStato() == EDITOR_TEST) {
        return test->aggiornaStato();
    } else {
        return aggiornaStatoEditor();
    }
}

int Editor::aggiornaStatoEditor() {
    return Livello::aggiornaStato();
}

int Editor::video() {
    if (gioco->getStato() == EDITOR_TEST) {
        return test->video();
    } else {
        return videoEditor();
    }
}

int Editor::videoEditor() {
//    ElementoAttivo *p_aux_pezzo, *p_aux_base;
    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
    if (azione_continua == 0 && getMousePosGrigliaXY(gioco->getWindowA())) {
        //        //cubo_selezione[pos_x_griglia][pos_y_griglia] = 1;
        //        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi)
        //
        //        if (caratteristiche_selezione == DAVANTI_BASE || entrambi)
        //
        //
        if (caratteristiche_selezione == DAVANTI_PEZZO) {
            griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
//            p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
//            p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
            //            if (p_aux_pezzo->occupata) {
            //                if (p_aux_pezzo->tipo == ELEM_PEZZO)
            //                    p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
            //            } else {
            //                p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
            //            }
        }
        else if (caratteristiche_selezione == DAVANTI_BASE) {
            griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata,ELEM_BASE);
//            p_aux_base = griglia_livello.getPosizione(x_base_selezionata, y_base_selezionata);
//            p_aux_base->attivaSelezione(ELEM_BASE);
            //            if (p_aux_base->occupata) {
            //                if (p_aux_base->tipo == ELEM_BASE)
            //                    p_aux_base->attivaSelezione(ELEM_BASE);
            //            } else {
            //                p_aux_base->attivaSelezione(ELEM_BASE);
            //            }
        }
    }
    return Livello::video();
}

int Editor::gestisciInput(SDL_Event *evento) {
    if (gioco->getStato() == EDITOR_TEST) {
        return test->gestisciInput(evento);
    } else {
        return gestisciInputEditor(evento);
    }
}

int Editor::gestisciInputEditor(SDL_Event *evento) {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        if (Livello::gestisciInput(evento)) {
            switch (evento->type) {
                case SDL_KEYDOWN:
                    switch (evento->key.keysym.sym) {
                        case SDLK_1:
                            posiziona_pezzi = true;
                            posiziona_basi = false;
                            azione_continua = 0;
                            break;
                        case SDLK_2:
                            posiziona_pezzi = false;
                            posiziona_basi = true;
                            azione_continua = 0;
                            break;
                        case SDLK_F5:
                            gioco->setStato(EDITOR_TEST);
                            if (test_partita_allocata) {
                                delete test;
                                test = new Partita(*this);
                            } else {
                                test_partita_allocata = true;
                                test = new Partita(*this);
                            }
                            break;
                        default:
                            break;

                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evento->button.button == SDL_BUTTON_LEFT && getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        mouseSelezione(gioco->getWindowA());
//                        ElementoAttivo *p_aux_pezzo, *p_aux_base;
                        if (caratteristiche_selezione == DAVANTI_PEZZO) {
//                            p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
                            if (griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                                //if (p_aux_pezzo->tipo == ELEM_PEZZO) {
                                griglia_livello.eliminaElemento(x_pezzo_selezionato,y_pezzo_selezionato);
                                azione_continua = ELIMINA_PEZZI;
                                //}
                            } else {
                                griglia_livello.creaElemento(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
                                azione_continua = POSIZIONA_PEZZI;
                            }
                            griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
                        }
                        else if (caratteristiche_selezione == DAVANTI_BASE) {
//                            p_aux_base = griglia_livello.getPosizione(x_base_selezionata, y_base_selezionata);
                            if (griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)) {
                                griglia_livello.eliminaElemento(x_base_selezionata, y_base_selezionata);
                                azione_continua = ELIMINA_BASI;
                            } else {
                                griglia_livello.creaElemento(x_base_selezionata, y_base_selezionata,ELEM_BASE);
                                azione_continua = POSIZIONA_BASI;
                            }
                            griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata,ELEM_BASE);
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        mouseSelezione(gioco->getWindowA());
//                        ElementoAttivo *p_aux_pezzo, *p_aux_base;
//                        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi)
//                            p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
//                        if (caratteristiche_selezione == DAVANTI_BASE || entrambi)
//                            p_aux_base = griglia_livello.getPosizione(x_base_selezionata, y_base_selezionata);
                        switch (azione_continua) {
                            case POSIZIONA_PEZZI:
                                if ((caratteristiche_selezione == DAVANTI_PEZZO || entrambi) && !griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)) {
                                    griglia_livello.creaElemento(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
                                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
                                }
                                break;
                            case POSIZIONA_BASI:
                                if ((caratteristiche_selezione == DAVANTI_BASE || entrambi) && !griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)) {
                                    griglia_livello.creaElemento(x_base_selezionata, y_base_selezionata,ELEM_BASE);
                                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata,ELEM_BASE);
                                }
                                break;
                            case ELIMINA_PEZZI:
                                if ((caratteristiche_selezione == DAVANTI_PEZZO || entrambi) && griglia_livello.getOccupato(x_pezzo_selezionato, y_pezzo_selezionato)
                                        && griglia_livello.getTipo(x_pezzo_selezionato, y_pezzo_selezionato) == ELEM_PEZZO) {
                                    griglia_livello.eliminaElemento(x_pezzo_selezionato,y_pezzo_selezionato);
                                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
                                }
                                break;
                            case ELIMINA_BASI:
                                if ((caratteristiche_selezione == DAVANTI_BASE || entrambi) && griglia_livello.getOccupato(x_base_selezionata, y_base_selezionata)
                                        && griglia_livello.getTipo(x_base_selezionata, y_base_selezionata) == ELEM_BASE) {
                                    griglia_livello.eliminaElemento(x_base_selezionata, y_base_selezionata);
                                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata,ELEM_BASE);
                                }
                                break;
                            default:
                                if (caratteristiche_selezione == DAVANTI_PEZZO) {
                                    griglia_livello.attivaSelezione(x_pezzo_selezionato, y_pezzo_selezionato,ELEM_PEZZO);
                                }
                                if (caratteristiche_selezione == DAVANTI_BASE) {
                                    griglia_livello.attivaSelezione(x_base_selezionata, y_base_selezionata,ELEM_BASE);
                                }
                                break;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (evento->button.button == SDL_BUTTON_LEFT) {
                        azione_continua = 0;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}



