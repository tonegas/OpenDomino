/* 
 * File:   TelecameraProspettica.cpp
 * Author: tonegas
 * 
 * Created on 14 novembre 2009, 23.38
 */

#include "../include/Domino.h"

TelecameraProspettica::TelecameraProspettica(unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux)
: Telecamera(dim_grilia_X_aux, dim_grilia_Y_aux) {
    max_z = PROSPETTICA_Z_MAX;
    min_z = PROSPETTICA_Z_MIN;
    delta_z = PROSPETTICA_DELTA_Z;
    tempo_reset_delta_z = 0;
    mouvi_z = false;
}

TelecameraProspettica::TelecameraProspettica(const TelecameraProspettica& orig) : Telecamera(orig) {
    max_z = PROSPETTICA_Z_MAX;
    min_z = PROSPETTICA_Z_MIN;
    delta_z = PROSPETTICA_DELTA_Z;
    posizione_telecamera = orig.posizione_telecamera;
    posizione_telecamera_iniziale = orig.posizione_telecamera_iniziale;
    tempo_reset_delta_z = 0;
    mouvi_z = false;
}

TelecameraProspettica::TelecameraProspettica(PosTeleProsp &pos_tele_aux, unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux)
: Telecamera(dim_grilia_X_aux, dim_grilia_Y_aux) {
    posizione_telecamera = pos_tele_aux;
    max_z = PROSPETTICA_Z_MAX;
    min_z = PROSPETTICA_Z_MIN;
    delta_z = PROSPETTICA_DELTA_Z;
    tempo_reset_delta_z = 0;
    mouvi_z = false;
}

void TelecameraProspettica::configuraVisuale() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(PROSPETTICA_FOVY, (GLfloat) matrice_view[2] / (GLfloat) matrice_view[3], PROSPETTICA_ZNEAR, PROSPETTICA_ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            PROSPETTICA_X_TELECAMERA, PROSPETTICA_Y_TELECAMERA, PROSPETTICA_Z_TELECAMERA, /* eye  */
            PROSPETTICA_X_TELECAMERA, PROSPETTICA_Y_TELECAMERA, 0.0, /* center  */
            0.0, 1.0, 0.0);
}

void TelecameraProspettica::setProiezioneTelecamera(int larghezza_fin, int altezza_fin) {
    glViewport(0, 0, (GLint) larghezza_fin, (GLint) altezza_fin);
    glGetIntegerv(GL_VIEWPORT, matrice_view);

    configuraVisuale();
    glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model);
    glGetDoublev(GL_PROJECTION_MATRIX, matrice_proj);

    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);

    //resetto il movimento dello zoom
    mouvi_z = false;
    //        //recupero pa posizione z della superfice
    GLdouble mouse_x, mouse_y;
    gluProject(0.0, 0.0, 0.0, matrice_model, matrice_proj, matrice_view, &mouse_x, &mouse_y, &mouse_z_fin_double);
    getMousePosGrigliaXY();
}

bool TelecameraProspettica::getMousePosGrigliaXY() {
    GLuint buffer[4]; // Set Up A Selection Buffer
    GLint hits;
    glSelectBuffer(4, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (matrice_view[3] - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        gluPerspective(PROSPETTICA_FOVY, (GLfloat) matrice_view[2] / (GLfloat) matrice_view[3], PROSPETTICA_ZNEAR, PROSPETTICA_ZFAR);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glLoadName(0);
            visualeOpenGL();
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
        GLuint depth = buffer[2]; // Store How Far Away It Is
        gluUnProject(mouse_x_fin, (GLfloat) (matrice_view[3] - mouse_y_fin), (GLdouble) depth / (GLdouble) (GLuint) (-1), matrice_model_griglia, matrice_proj, matrice_view, &pos_x_griglia, &pos_y_griglia, &pos_z_griglia);
        indice_x_griglia = pos_x_griglia / (GLfloat) ALTEZZA_PEZZO;
        indice_y_griglia = pos_y_griglia / (GLfloat) ALTEZZA_PEZZO;
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

bool TelecameraProspettica::getMousePosGrigliaXYIniziale() {
    GLuint buffer[4]; // Set Up A Selection Buffer
    GLint hits;
    glSelectBuffer(4, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (matrice_view[3] - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        gluPerspective(PROSPETTICA_FOVY, (GLfloat) matrice_view[2] / (GLfloat) matrice_view[3], PROSPETTICA_ZNEAR, PROSPETTICA_ZFAR);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            glLoadName(0);
            visualeOpenGLIniziale();
            glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model_griglia);
            glBegin(GL_QUADS);
            {
                glNormal3f(0.0, 0.0, 1.0);
                glVertex3f(-ALTEZZA_PEZZO * 100, -ALTEZZA_PEZZO * 100, 0);
                glVertex3f(dim_grilia_X * ALTEZZA_PEZZO + ALTEZZA_PEZZO * 100, -ALTEZZA_PEZZO * 100, 0);
                glVertex3f(dim_grilia_X * ALTEZZA_PEZZO + ALTEZZA_PEZZO * 100, dim_grilia_Y * ALTEZZA_PEZZO + ALTEZZA_PEZZO * 100, 0);
                glVertex3f(-ALTEZZA_PEZZO * 100, dim_grilia_Y * ALTEZZA_PEZZO + ALTEZZA_PEZZO * 100, 0);
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
        gluUnProject(mouse_x_fin, (GLfloat) (matrice_view[3] - mouse_y_fin), (GLdouble) buffer[2] / (GLdouble) (GLuint) (-1), matrice_model_griglia, matrice_proj, matrice_view, &pos_x_griglia, &pos_y_griglia, &pos_z_griglia);
    }
    return true;
}

bool TelecameraProspettica::mouseSelezione(Livello *liv, Griglia* griglia_livello) {
    GLuint buffer[36]; // Set Up A Selection Buffer
    GLint hits = 0;
    glSelectBuffer(36, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) ((GLfloat) (matrice_view[3] - matrice_view[1]) - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        gluPerspective(PROSPETTICA_FOVY, (GLfloat) (matrice_view[2] - matrice_view[0]) / (GLfloat) (matrice_view[3] - matrice_view[1]), PROSPETTICA_ZNEAR, PROSPETTICA_ZFAR);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {
            visualeOpenGL();
            int indice = 1;
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
    pos_x_iniziale = pos_x;
    pos_y_iniziale = pos_y;
    pos_x_griglia_iniziale = pos_x_griglia;
    pos_y_griglia_iniziale = pos_y_griglia;
    posizione_telecamera_iniziale = posizione_telecamera;
}

void TelecameraProspettica::registraZoomAvanti() {
    if (posizione_telecamera.z < max_z) {
        if (posizione_telecamera.z + delta_z < max_z) {
            //            posizione_telecamera_iniziale.x = posizione_telecamera.x + (1 - delta_z)*(pos_x - posizione_telecamera.x);
            //            posizione_telecamera_iniziale.y = posizione_telecamera.y + (1 - delta_z)*(pos_y - posizione_telecamera.y);
            posizione_telecamera_iniziale.z = posizione_telecamera.z + delta_z;
            delta_z *= PROSPETTICA_INCREMENTO_DELTA_Z;
        } else {
            delta_z = PROSPETTICA_DELTA_Z;
            //            posizione_telecamera_iniziale.x = posizione_telecamera.x + (1 - (GLfloat) max_z / posizione_telecamera.z)*(pos_x - posizione_telecamera.x);
            //            posizione_telecamera_iniziale.y = posizione_telecamera.y + (1 - (GLfloat) max_z / posizione_telecamera.z)*(pos_y - posizione_telecamera.y);
            posizione_telecamera_iniziale.z = max_z;
        }
        mouvi_z = true;
    }
}

void TelecameraProspettica::registraZoomIndietro() {
    if (posizione_telecamera.z > min_z) {
        if (posizione_telecamera.z - delta_z > min_z) {
            //            posizione_telecamera_iniziale.x = posizione_telecamera.x + ((delta_z - 1) / delta_z)*(pos_x - posizione_telecamera.x);
            //            posizione_telecamera_iniziale.y = posizione_telecamera.y + ((delta_z - 1) / delta_z)*(pos_y - posizione_telecamera.y);
            posizione_telecamera_iniziale.z = posizione_telecamera.z - delta_z;
            delta_z *= PROSPETTICA_INCREMENTO_DELTA_Z;
        } else {
            delta_z = PROSPETTICA_DELTA_Z;
            //            posizione_telecamera_iniziale.x = posizione_telecamera.x + (((posizione_telecamera.z / (GLfloat) min_z) - 1) / (posizione_telecamera.z / (GLfloat) min_z))*(pos_x - posizione_telecamera.x);
            //            posizione_telecamera_iniziale.y = posizione_telecamera.y + (((posizione_telecamera.z / (GLfloat) min_z) - 1) / (posizione_telecamera.z / (GLfloat) min_z))*(pos_y - posizione_telecamera.y);
            posizione_telecamera_iniziale.z = min_z;
        }
        mouvi_z = true;
    }
}

void TelecameraProspettica::cambiaXY() {
    getMousePosGrigliaXYIniziale();
    posizione_telecamera.x = posizione_telecamera_iniziale.x + (pos_x_griglia - pos_x_griglia_iniziale);
    posizione_telecamera.y = posizione_telecamera_iniziale.y + (pos_y_griglia - pos_y_griglia_iniziale);
}

void TelecameraProspettica::cambiaAngolazione() {
    GLfloat nuovo_angolo_x = posizione_telecamera_iniziale.ang_x + (pos_x_iniziale - pos_x) / 4;
    GLfloat nuovo_angolo_y = posizione_telecamera_iniziale.ang_y + (pos_y_iniziale - pos_y) / 4;
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
        if (fabs(posizione_telecamera.z - posizione_telecamera_iniziale.z) >= 0.001) {
            //            posizione_telecamera.x += (posizione_telecamera_iniziale.x - posizione_telecamera.x) / 10;
            //            posizione_telecamera.y += (posizione_telecamera_iniziale.y - posizione_telecamera.y) / 10;
            posizione_telecamera.z += (posizione_telecamera_iniziale.z - posizione_telecamera.z) / 10;
        } else {
            mouvi_z = false;
            //            posizione_telecamera.x = posizione_telecamera_iniziale.x;
            //            posizione_telecamera.y = posizione_telecamera_iniziale.y;
            posizione_telecamera.z = posizione_telecamera_iniziale.z;
        }
    }
}

void TelecameraProspettica::controlloPosizione() {
    //cout << 'x' << posizione_telecamera.x << 'y' << posizione_telecamera.y << '\n' << flush;
    if (posizione_telecamera.x > 0) {
        posizione_telecamera.x = 0;
    } else {
        if (posizione_telecamera.x < -(GLdouble) (dim_grilia_X * ALTEZZA_PEZZO)) {
            posizione_telecamera.x = -(GLdouble) (dim_grilia_X * ALTEZZA_PEZZO);
        }
    }
    if (posizione_telecamera.y > 0) {
        posizione_telecamera.y = 0;
    } else {
        if (posizione_telecamera.y < -(GLdouble) (dim_grilia_Y * ALTEZZA_PEZZO)) {
            posizione_telecamera.y = -(GLdouble) (dim_grilia_Y * ALTEZZA_PEZZO);
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
    glTranslatef(0, 0, posizione_telecamera.z);
    glRotatef(posizione_telecamera.ang_y, 1, 0, 0);
    glRotatef(-posizione_telecamera.ang_x, 0, 1, 0);
    glTranslatef(posizione_telecamera.x, posizione_telecamera.y, 0);
    //glScalef(posizione_telecamera.z, posizione_telecamera.z, posizione_telecamera.z);
}

void TelecameraProspettica::visualeOpenGLIniziale() {
    glTranslatef(0, 0, posizione_telecamera_iniziale.z);
    glRotatef(posizione_telecamera_iniziale.ang_y, 1, 0, 0);
    glRotatef(-posizione_telecamera_iniziale.ang_x, 0, 1, 0);
    glTranslatef(posizione_telecamera_iniziale.x, posizione_telecamera_iniziale.y, 0);
    //glScalef(posizione_telecamera_iniziale.z, posizione_telecamera_iniziale.z, posizione_telecamera_iniziale.z);
}

PosTeleProsp* TelecameraProspettica::getPosTeleProsp() {
    return &posizione_telecamera;
}