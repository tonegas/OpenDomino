/* 
 * File:   TelecameraAssionometrica.cpp
 * Author: tonegas
 * 
 * Created on 14 novembre 2009, 23.34
 */

#include "../include/Domino.h"

TelecameraAssionometrica::TelecameraAssionometrica() : Telecamera() {
    delta_zoom = ASSIONOMETRICA_DELTA_ZOOM;
    max_zoom = ASSIONOMETRICA_ZOOM_MAX;
    min_zoom = ASSIONOMETRICA_ZOOM_MIN;
    tempo_reset_delta_zoom = 0;
    mouvi_zoom = false;
}

TelecameraAssionometrica::TelecameraAssionometrica(const TelecameraAssionometrica& orig) {
    delta_zoom = ASSIONOMETRICA_DELTA_ZOOM;
    max_zoom = ASSIONOMETRICA_ZOOM_MAX;
    min_zoom = ASSIONOMETRICA_ZOOM_MIN;
    posizione_telecamera = orig.posizione_telecamera;
    aux_posizione_telecamera = orig.aux_posizione_telecamera;
    tempo_reset_delta_zoom = 0;
    mouvi_zoom = false;
}

TelecameraAssionometrica::TelecameraAssionometrica(PosTeleAssio &pos_tele_aux) {
    posizione_telecamera = pos_tele_aux;
}

void TelecameraAssionometrica::setProiezioneTelecamera(int larghezza_fin, int altezza_fin) {
    glViewport(0, 0, (GLint) larghezza_fin, (GLint) altezza_fin);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (GLfloat) larghezza_fin,
            0, (GLfloat) altezza_fin,
            ASSIONOMETRICA_ZNEAR, ASSIONOMETRICA_ZFAR); //misure rispetto alla posizione dell'occhio
    glMultMatrixf(cavalier);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            ASSIONOMETRICA_X_TELECAMERA, ASSIONOMETRICA_Y_TELECAMERA, ASSIONOMETRICA_Z_TELECAMERA, /* eye  */
            ASSIONOMETRICA_X_TELECAMERA, ASSIONOMETRICA_Y_TELECAMERA, 0.0, /* center  */
            0.0, 1.0, 0.0); /* up is in positive Y direction */


    glGetIntegerv(GL_VIEWPORT, matrice_view);
    glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model);
    glGetDoublev(GL_PROJECTION_MATRIX, matrice_proj);

    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);

    //resetto il movimento dello zoom
    mouvi_zoom = false;

    //        //recupero pa posizione z della superfice
    GLdouble mouse_x, mouse_y;
    gluProject(0.0, 0.0, 0.0, matrice_model, matrice_proj, matrice_view, &mouse_x, &mouse_y, &mouse_z_fin_double);
}

bool TelecameraAssionometrica::getMousePosGrigliaXY(unsigned dim_grilia_X, unsigned dim_grilia_Y) {
    gluUnProject(mouse_x_fin, matrice_view[3] - mouse_y_fin, mouse_z_fin_double, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
    pos_x_griglia = ((pos_x - posizione_telecamera.x) / posizione_telecamera.zoom);
    pos_y_griglia = ((pos_y - posizione_telecamera.y) / posizione_telecamera.zoom);
    indice_x_griglia = (unsigned) (pos_x_griglia / (GLfloat) ALTEZZA_PEZZO);
    indice_y_griglia = (unsigned) (pos_y_griglia / (GLfloat) ALTEZZA_PEZZO);
    if (indice_x_griglia < dim_grilia_X && indice_y_griglia < dim_grilia_Y) {
        indice_griglia_ok = true;
    } else {
        indice_griglia_ok = false;
    }
    return indice_griglia_ok;
}

bool TelecameraAssionometrica::mouseSelezione(Livello *liv, Griglia* griglia_livello) {
    GLuint buffer[512]; // Set Up A Selection Buffer
    GLint hits = 0;
    glSelectBuffer(512, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (matrice_view[3] - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        glOrtho(0, (GLfloat) matrice_view[2], 0, (GLfloat) matrice_view[3], ASSIONOMETRICA_ZNEAR, ASSIONOMETRICA_ZFAR);
        glMultMatrixf(cavalier);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glTranslatef(posizione_telecamera.x, posizione_telecamera.y, 0);
            glScalef(posizione_telecamera.zoom, posizione_telecamera.zoom, posizione_telecamera.zoom);
            int indice = 1;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if ((int) indice_x_griglia + i >= 0 && (int) indice_x_griglia + i < (int) griglia_livello->getDimGrigliaX() &&
                            (int) indice_y_griglia + j >= 0 && (int) indice_y_griglia + j < (int) griglia_livello->getDimGrigliaX()) {
                        if (griglia_livello->getOccupato(indice_x_griglia + i, indice_y_griglia + j)) {
                            if (griglia_livello->getTipo(indice_x_griglia + i, indice_y_griglia + j) == ELEM_PEZZO) {
                                glLoadName((i + 1) * 3 + (j + 1) + 1);
                                Pezzo::stampaPezzoCollisione(indice_x_griglia + i, indice_y_griglia + j);
                            } else {
                                glLoadName(11 + (i + 1) * 3 + (j + 1));
                                Base::stampaBaseCollisione(indice_x_griglia + i, indice_y_griglia + j);
                            }
                        } else {
                            glLoadName((i + 1) * 3 + (j + 1) + 1);
                            Pezzo::stampaPezzoCollisione(indice_x_griglia + i, indice_y_griglia + j);
                            glLoadName(11 + (i + 1) * 3 + (j + 1));
                            Base::stampaBaseCollisione(indice_x_griglia + i, indice_y_griglia + j);
                        }
                        indice++;
                    }
                }
            }
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    hits = glRenderMode(GL_RENDER);
    liv->resettaSelezione(); //caratteristiche selezione niente entrambi false
    if (hits > 0) // If There Were More Than 0 Hits
    {
        unsigned distanza = -1;
        for (int loop = 0; loop < hits; loop++) {
            if (buffer[loop * 4 + 3] < 10) {
                if (distanza > buffer[loop * 4 + 1]) {
                    liv->selezioneDavantiPezzo(indice_x_griglia + ((buffer[loop * 4 + 3] - 1) / 3 - 1), indice_y_griglia + ((buffer[loop * 4 + 3] - 1) % 3 - 1));
                    distanza = buffer[loop * 4 + 1];
                }
            } else {
                if (distanza > buffer[loop * 4 + 1]) {
                    liv->selezioneDavantiBase(indice_x_griglia + ((buffer[loop * 4 + 3] - 11) / 3 - 1), indice_y_griglia + ((buffer[loop * 4 + 3] - 11) % 3 - 1));
                    distanza = buffer[loop * 4 + 1];
                }
            }
        }
    }
    return 0;
}

void TelecameraAssionometrica::registraPosizione() {
    pos_x_iniziali = pos_x;
    pos_y_iniziali = pos_y;
    aux_posizione_telecamera = posizione_telecamera;
}

void TelecameraAssionometrica::registraZoomAvanti() {
    if (posizione_telecamera.zoom < max_zoom) {
        if (posizione_telecamera.zoom * delta_zoom < max_zoom) {
            aux_posizione_telecamera.zoom = posizione_telecamera.zoom * delta_zoom;
            aux_posizione_telecamera.x = posizione_telecamera.x + (1 - delta_zoom)*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + (1 - delta_zoom)*(pos_y - posizione_telecamera.y);
            delta_zoom *= ASSIONOMETRICA_INCREMENTO_DELTA_ZOOM;
        } else {
            delta_zoom = ASSIONOMETRICA_DELTA_ZOOM;
            aux_posizione_telecamera.zoom = max_zoom;
            aux_posizione_telecamera.x = posizione_telecamera.x + (1 - (GLfloat) max_zoom / posizione_telecamera.zoom)*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + (1 - (GLfloat) max_zoom / posizione_telecamera.zoom)*(pos_y - posizione_telecamera.y);
        }
        mouvi_zoom = true;
    }
}

void TelecameraAssionometrica::registraZoomIndietro() {
    if (posizione_telecamera.zoom > min_zoom) {
        if (posizione_telecamera.zoom / delta_zoom > min_zoom) {
            aux_posizione_telecamera.zoom = posizione_telecamera.zoom / delta_zoom;
            aux_posizione_telecamera.x = posizione_telecamera.x + ((delta_zoom - 1) / delta_zoom)*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + ((delta_zoom - 1) / delta_zoom)*(pos_y - posizione_telecamera.y);
            delta_zoom *= ASSIONOMETRICA_INCREMENTO_DELTA_ZOOM;
        } else {
            delta_zoom = ASSIONOMETRICA_DELTA_ZOOM;
            aux_posizione_telecamera.zoom = min_zoom;
            aux_posizione_telecamera.x = posizione_telecamera.x + (((posizione_telecamera.zoom / (GLfloat) min_zoom) - 1) / (posizione_telecamera.zoom / (GLfloat) min_zoom))*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + (((posizione_telecamera.zoom / (GLfloat) min_zoom) - 1) / (posizione_telecamera.zoom / (GLfloat) min_zoom))*(pos_y - posizione_telecamera.y);
        }
        mouvi_zoom = true;
    }
}

void TelecameraAssionometrica::cambiaXY() {
    posizione_telecamera.x = aux_posizione_telecamera.x + (pos_x - pos_x_iniziali);
    posizione_telecamera.y = aux_posizione_telecamera.y + (pos_y - pos_y_iniziali);
}

void TelecameraAssionometrica::animaZoom() {
    if (mouvi_zoom) {
        if (fabs(posizione_telecamera.zoom - aux_posizione_telecamera.zoom) >= 0.001) {
            posizione_telecamera.x += (aux_posizione_telecamera.x - posizione_telecamera.x) / 10;
            posizione_telecamera.y += (aux_posizione_telecamera.y - posizione_telecamera.y) / 10;
            posizione_telecamera.zoom += (aux_posizione_telecamera.zoom - posizione_telecamera.zoom) / 10;
        } else {
            mouvi_zoom = false;
            posizione_telecamera.x = aux_posizione_telecamera.x;
            posizione_telecamera.y = aux_posizione_telecamera.y;
            posizione_telecamera.zoom = aux_posizione_telecamera.zoom;
        }
    }
}

void TelecameraAssionometrica::controlloPosizione(unsigned dim_grilia_X, unsigned dim_grilia_Y) {
    if (posizione_telecamera.x > 0) {
        posizione_telecamera.x = 0;
    } else {
        if (posizione_telecamera.x < -(GLdouble) (dim_grilia_X * ALTEZZA_PEZZO) * posizione_telecamera.zoom) {
            posizione_telecamera.x = -(GLdouble) (dim_grilia_X * ALTEZZA_PEZZO) * posizione_telecamera.zoom;
        }
    }
    if (posizione_telecamera.y > 0) {
        posizione_telecamera.y = 0;
    } else {
        if (posizione_telecamera.y < -(GLdouble) (dim_grilia_Y * ALTEZZA_PEZZO) * posizione_telecamera.zoom) {
            posizione_telecamera.y = -(GLdouble) (dim_grilia_Y * ALTEZZA_PEZZO) * posizione_telecamera.zoom;
        }
    }
}

void TelecameraAssionometrica::resettaDeltaZoom(int frame_ms) {
    if (delta_zoom > ASSIONOMETRICA_DELTA_ZOOM) {
        tempo_reset_delta_zoom++;
        if (tempo_reset_delta_zoom == (1000 / frame_ms)) {
            tempo_reset_delta_zoom = 0;
            delta_zoom = ASSIONOMETRICA_DELTA_ZOOM;
        }
    }
}

void TelecameraAssionometrica::visualeOpenGL() {
    glTranslatef(posizione_telecamera.x, posizione_telecamera.y, 0);
    glScalef(posizione_telecamera.zoom, posizione_telecamera.zoom, posizione_telecamera.zoom);
}
