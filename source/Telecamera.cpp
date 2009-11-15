/* 
 * File:   Telecamera.cpp
 * Author: tonegas
 * 
 * Created on 14 novembre 2009, 23.31
 */

#include "../include/Domino.h"

Telecamera::Telecamera() {
}

Telecamera::Telecamera(const Telecamera& orig) {
}

bool Telecamera::getMousePosGrigliaXY(int mouse_x_fin_aux, int mouse_y_fin_aux, unsigned dim_grilia_X, unsigned dim_grilia_Y) {
    mouse_x_fin = mouse_x_fin_aux;
    mouse_y_fin = mouse_y_fin_aux;
    return getMousePosGrigliaXY(dim_grilia_X, dim_grilia_Y);
}

void Telecamera::aggiorna(unsigned dim_grilia_X, unsigned dim_grilia_Y, int frame_ms) {
    animaZoom();
    controlloPosizione(dim_grilia_X, dim_grilia_Y);
    resettaDeltaZoom(frame_ms);
}