/* 
 * File:   Telecamera.cpp
 * Author: tonegas
 * 
 * Created on 14 novembre 2009, 23.31
 */

#include "../include/Domino.h"

Telecamera::Telecamera(unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux) {
    dim_grilia_X = dim_grilia_X_aux;
    dim_grilia_Y = dim_grilia_Y_aux;
}

Telecamera::Telecamera(const Telecamera& orig) {
    dim_grilia_X = orig.dim_grilia_X;
    dim_grilia_Y = orig.dim_grilia_Y;
}

bool Telecamera::getMousePosGrigliaXY(int mouse_x_fin_aux, int mouse_y_fin_aux) {
    if (mouse_x_fin != mouse_x_fin_aux || mouse_y_fin != mouse_y_fin_aux) {
        mouse_x_fin = mouse_x_fin_aux;
        mouse_y_fin = mouse_y_fin_aux;
        return getMousePosGrigliaXY();
    } else {
        return indice_griglia_ok;
    }
}

void Telecamera::aggiorna(int frame_ms) {
    animaZoom();
    controlloPosizione();
    resettaDeltaZoom(frame_ms);
}