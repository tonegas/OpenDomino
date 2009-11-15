/* 
 * File:   TelecameraProspettica.cpp
 * Author: tonegas
 * 
 * Created on 14 novembre 2009, 23.38
 */

#include "../include/Domino.h"

TelecameraProspettica::TelecameraProspettica() : Telecamera() {
    max_z = PROSPETTICA_Z_MAX;
    min_z = PROSPETTICA_Z_MIN;
    delta_z = PROSPETTICA_DELTA_Z;
    tempo_reset_delta_z = 0;
    mouvi_z = false;
}

TelecameraProspettica::TelecameraProspettica(const TelecameraProspettica& orig) {
    max_z = PROSPETTICA_Z_MAX;
    min_z = PROSPETTICA_Z_MIN;
    delta_z = PROSPETTICA_DELTA_Z;
    posizione_telecamera = orig.posizione_telecamera;
    aux_posizione_telecamera = orig.aux_posizione_telecamera;
    tempo_reset_delta_z = 0;
    mouvi_z = false;
}

TelecameraProspettica::TelecameraProspettica(PosTeleProsp &pos_tele_aux) {
    posizione_telecamera = pos_tele_aux;
}

void TelecameraProspettica::setProiezioneTelecamera(int larghezza_fin, int altezza_fin) {
    glViewport(0, 0, (GLint) larghezza_fin, (GLint) altezza_fin);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(PROSPETTICA_FOVY, (GLfloat) larghezza_fin / (GLfloat) altezza_fin, PROSPETTICA_ZNEAR, PROSPETTICA_ZFAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            PROSPETTICA_X_TELECAMERA, PROSPETTICA_Y_TELECAMERA, PROSPETTICA_Z_TELECAMERA, /* eye  */
            PROSPETTICA_X_TELECAMERA, PROSPETTICA_Y_TELECAMERA, 0.0, /* center  */
            0.0, 1.0, 0.0); /* up is in positive Y direction */

    glGetIntegerv(GL_VIEWPORT, matrice_view);
    glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model);
    glGetDoublev(GL_PROJECTION_MATRIX, matrice_proj);

    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);

    //resetto il movimento dello zoom
    mouvi_z = false;
    //        //recupero pa posizione z della superfice
    GLdouble mouse_x, mouse_y;
    gluProject(0.0, 0.0, 0.0, matrice_model, matrice_proj, matrice_view, &mouse_x, &mouse_y, &mouse_z_fin_double);
}

bool TelecameraProspettica::getMousePosGrigliaXY(unsigned dim_grilia_X, unsigned dim_grilia_Y) {
    GLuint buffer[512]; // Set Up A Selection Buffer
    GLint hits;
    glSelectBuffer(512, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (matrice_view[3] - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        gluPerspective(FOVY, (GLfloat) matrice_view[2] / (GLfloat) matrice_view[3], PROSPETTICA_ZNEAR, PROSPETTICA_ZFAR);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glLoadName(0);
            glRotatef(posizione_telecamera.ang_y, 1, 0, 0);
            glRotatef(-posizione_telecamera.ang_x, 0, 1, 0);
            glTranslatef(posizione_telecamera.x, posizione_telecamera.y, 0);
            glScalef(posizione_telecamera.z, posizione_telecamera.z, posizione_telecamera.z);
            glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model_griglia);
            glBegin(GL_QUADS);
            {
                glNormal3f(0.0, 0.0, 1.0);
                glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
                glVertex3f(dim_grilia_X * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
                glVertex3f(dim_grilia_X * ALTEZZA_PEZZO + ALTEZZA_PEZZO, dim_grilia_Y * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
                glVertex3f(-ALTEZZA_PEZZO, dim_grilia_Y * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
            }
            glEnd();
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    hits = glRenderMode(GL_RENDER);
    if (hits > 0) // If There Were More Than 0 Hits
    {
        //int choose = buffer[3]; // Make Our Selection The First Object
        GLuint depth = buffer[2]; // Store How Far Away It Is
        //cout << "depth:" << (GLfloat) depth / (GLfloat) (GLuint) (-1) << '\t' << superfice_z << '\n' << flush;
        gluUnProject(mouse_x_fin, (GLfloat) (matrice_view[3] - mouse_y_fin), (GLdouble) depth / (GLdouble) (GLuint) (-1), matrice_model_griglia, matrice_proj, matrice_view, &pos_x_griglia, &pos_y_griglia, &pos_z_griglia);
        indice_x_griglia = pos_x_griglia / (GLfloat) ALTEZZA_PEZZO;
        indice_y_griglia = pos_y_griglia / (GLfloat) ALTEZZA_PEZZO;
        //cout<<indice_x_griglia<<' '<<indice_y_griglia<<'\n'<<flush;
        if (indice_x_griglia < dim_grilia_X && indice_y_griglia < dim_grilia_Y) {
            indice_griglia_ok = true;
        } else {
            indice_griglia_ok = false;
        }
    } else {
        indice_griglia_ok = false;
    }
    gluUnProject(mouse_x_fin, (GLfloat) (matrice_view[3] - mouse_y_fin), mouse_z_fin_double, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
    return indice_griglia_ok;
}

bool TelecameraProspettica::mouseSelezione(Livello *liv, Griglia* griglia_livello) {
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
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) ((GLfloat) (matrice_view[3] - matrice_view[1]) - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        gluPerspective(FOVY, (GLfloat) (matrice_view[2] - matrice_view[0]) / (GLfloat) (matrice_view[3] - matrice_view[1]), ZNEAR, ZFAR);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glRotatef(posizione_telecamera.ang_y, 1, 0, 0);
            glRotatef(-posizione_telecamera.ang_x, 0, 1, 0);
            glTranslatef(posizione_telecamera.x, posizione_telecamera.y, 0);
            glScalef(posizione_telecamera.z, posizione_telecamera.z, posizione_telecamera.z);
            int indice = 1;
            cout << indice_x_griglia << ' ' << indice_y_griglia << '\n' << flush;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if ((int) indice_x_griglia + i >= 0 && (int) indice_x_griglia + i < (int) griglia_livello->getDimGrigliaX() &&
                            (int) indice_y_griglia + j >= 0 && (int) indice_y_griglia + j < (int) griglia_livello->getDimGrigliaY()) {
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

void TelecameraProspettica::registraPosizione() {
    pos_x_iniziali = pos_x;
    pos_y_iniziali = pos_y;
    aux_posizione_telecamera = posizione_telecamera;
}

void TelecameraProspettica::registraZoomAvanti() {
    if (posizione_telecamera.z < max_z) {
        if (posizione_telecamera.z * delta_z < max_z) {
            aux_posizione_telecamera.z = posizione_telecamera.z * delta_z;
            aux_posizione_telecamera.x = posizione_telecamera.x + (1 - delta_z)*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + (1 - delta_z)*(pos_y - posizione_telecamera.y);
            delta_z *= PROSPETTICA_INCREMENTO_DELTA_Z;
        } else {
            delta_z = PROSPETTICA_DELTA_Z;
            aux_posizione_telecamera.z = max_z;
            aux_posizione_telecamera.x = posizione_telecamera.x + (1 - (GLfloat) max_z / posizione_telecamera.z)*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + (1 - (GLfloat) max_z / posizione_telecamera.z)*(pos_y - posizione_telecamera.y);
        }
        mouvi_z = true;
    }
}

void TelecameraProspettica::registraZoomIndietro() {
    if (posizione_telecamera.z > min_z) {
        if (posizione_telecamera.z / delta_z > min_z) {
            aux_posizione_telecamera.z = posizione_telecamera.z / delta_z;
            aux_posizione_telecamera.x = posizione_telecamera.x + ((delta_z - 1) / delta_z)*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + ((delta_z - 1) / delta_z)*(pos_y - posizione_telecamera.y);
            delta_z *= PROSPETTICA_INCREMENTO_DELTA_Z;
        } else {
            delta_z = PROSPETTICA_DELTA_Z;
            aux_posizione_telecamera.z = min_z;
            aux_posizione_telecamera.x = posizione_telecamera.x + (((posizione_telecamera.z / (GLfloat) min_z) - 1) / (posizione_telecamera.z / (GLfloat) min_z))*(pos_x - posizione_telecamera.x);
            aux_posizione_telecamera.y = posizione_telecamera.y + (((posizione_telecamera.z / (GLfloat) min_z) - 1) / (posizione_telecamera.z / (GLfloat) min_z))*(pos_y - posizione_telecamera.y);
        }
        mouvi_z = true;
    }
}

void TelecameraProspettica::cambiaXY() {
    posizione_telecamera.x = aux_posizione_telecamera.x + (pos_x - pos_x_iniziali);
    posizione_telecamera.y = aux_posizione_telecamera.y + (pos_y - pos_y_iniziali);
}

void TelecameraProspettica::cambiaAngolazione() {
    GLfloat nuovo_angolo_x = aux_posizione_telecamera.ang_x + (pos_x_iniziali - pos_x);
    GLfloat nuovo_angolo_y = aux_posizione_telecamera.ang_y + (pos_y_iniziali - pos_y);
    if (fabs(nuovo_angolo_x) < PROSPETTICA_MAX_ANGOLO_TELECAMERA) {
        posizione_telecamera.ang_x = nuovo_angolo_x;
    } else {
        if (posizione_telecamera.ang_x < 0)
            posizione_telecamera.ang_x = -PROSPETTICA_MAX_ANGOLO_TELECAMERA;
        else
            posizione_telecamera.ang_x = PROSPETTICA_MAX_ANGOLO_TELECAMERA;
    }
    if (fabs(nuovo_angolo_y) < PROSPETTICA_MAX_ANGOLO_TELECAMERA) {
        posizione_telecamera.ang_y = nuovo_angolo_y;
    } else {
        if (nuovo_angolo_y < 0)
            posizione_telecamera.ang_y = -PROSPETTICA_MAX_ANGOLO_TELECAMERA;
        else
            posizione_telecamera.ang_y = PROSPETTICA_MAX_ANGOLO_TELECAMERA;
    }
}

void TelecameraProspettica::animaZoom() {
    if (mouvi_z) {
        if (fabs(posizione_telecamera.z - aux_posizione_telecamera.z) >= 0.001) {
            posizione_telecamera.x += (aux_posizione_telecamera.x - posizione_telecamera.x) / 10;
            posizione_telecamera.y += (aux_posizione_telecamera.y - posizione_telecamera.y) / 10;
            posizione_telecamera.z += (aux_posizione_telecamera.z - posizione_telecamera.z) / 10;
        } else {
            mouvi_z = false;
            posizione_telecamera.x = aux_posizione_telecamera.x;
            posizione_telecamera.y = aux_posizione_telecamera.y;
            posizione_telecamera.z = aux_posizione_telecamera.z;
        }
    }
}

void TelecameraProspettica::controlloPosizione(unsigned dim_grilia_X, unsigned dim_grilia_Y) {
    if (posizione_telecamera.x > 0) {
        posizione_telecamera.x = 0;
    } else {
        if (posizione_telecamera.x < -(GLdouble) (dim_grilia_X * ALTEZZA_PEZZO) * posizione_telecamera.z) {
            posizione_telecamera.x = -(GLdouble) (dim_grilia_X * ALTEZZA_PEZZO) * posizione_telecamera.z;
        }
    }
    if (posizione_telecamera.y > 0) {
        posizione_telecamera.y = 0;
    } else {
        if (posizione_telecamera.y < -(GLdouble) (dim_grilia_Y * ALTEZZA_PEZZO) * posizione_telecamera.z) {
            posizione_telecamera.y = -(GLdouble) (dim_grilia_Y * ALTEZZA_PEZZO) * posizione_telecamera.z;
        }
    }
}

void TelecameraProspettica::resettaDeltaZoom(int frame_ms) {
    if (delta_z > PROSPETTICA_DELTA_Z) {
        tempo_reset_delta_z++;
        if (tempo_reset_delta_z == (1000 / frame_ms)) {
            tempo_reset_delta_z = 0;
            delta_z = PROSPETTICA_DELTA_Z;
        }
    }
}

void TelecameraProspettica::visualeOpenGL() {
    glRotatef(posizione_telecamera.ang_y, 1, 0, 0);
    glRotatef(-posizione_telecamera.ang_x, 0, 1, 0);
    glTranslatef(posizione_telecamera.x, posizione_telecamera.y, 0);
    glScalef(posizione_telecamera.z, posizione_telecamera.z, posizione_telecamera.z);
}

