/* 
 * File:   Livello.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 16.03
 */

#include "../include/Livello.h"

Livello::Livello(int num_x_colonne_aux, int num_y_righe_aux) :
livello_editor(num_x_colonne_aux, num_y_righe_aux) {
    bottone_destro = false;
    bottone_sinistro = false;
}

bool Livello::getMousePosGrigliaXY(int larghezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux) {
    mouse_x_fin = mouse_x_fin_aux;
    mouse_y_fin = mouse_y_fin_aux;
    return getMousePosGrigliaXY(larghezza_fin);
}

bool Livello::getMousePosGrigliaXY(int larghezza_fin) {
    gluUnProject(mouse_x_fin, larghezza_fin - mouse_y_fin, superfice_z, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
    pos_x_griglia = (int) (((pos_x - livello_editor.getGriglia().x) / livello_editor.getGriglia().zoom) / (GLfloat) ALTEZZA_PEZZO);
    pos_y_griglia = (int) (((pos_y - livello_editor.getGriglia().y) / livello_editor.getGriglia().zoom) / (GLfloat) ALTEZZA_PEZZO);
    if (pos_x_griglia >= 0 && pos_y_griglia >= 0 && (unsigned) pos_x_griglia < livello_editor.getDimGrigliaX() && (unsigned) pos_y_griglia < livello_editor.getDimGrigliaY()) {
        pos_griglia_ok = true;
    } else {
        pos_griglia_ok = false;
    }
    return pos_griglia_ok;
}


