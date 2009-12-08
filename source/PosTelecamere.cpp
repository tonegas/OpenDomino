/* 
 * File:   PosTelecamere.cpp
 * Author: tonegas
 * 
 * Created on 30 novembre 2009, 15.38
 */

#include "../include/Domino.h"

PosTeleXY::PosTeleXY(GLfloat x_aux, GLfloat y_aux) {
    x = x_aux;
    y = y_aux;
}

PosTeleXY::PosTeleXY(const PosTeleXY &orig) {
    x = orig.x;
    y = orig.y;
}

PosTeleProsp::PosTeleProsp(GLfloat x_aux, GLfloat y_aux, GLfloat z_aux, GLfloat ang_x_aux, GLfloat ang_y_aux) {
    x = x_aux;
    y = y_aux;
    z = z_aux;
    ang_x = ang_x_aux;
    ang_y = ang_y_aux;
}

PosTeleProsp::PosTeleProsp(const PosTeleProsp& orig):PosTeleXY(orig.x, orig.y) {
    z = orig.z;
    ang_x = orig.ang_x;
    ang_y = orig.ang_y;
}

PosTeleAssio::PosTeleAssio(GLfloat x_aux, GLfloat y_aux, GLfloat zoom_aux) {
    x = x_aux;
    y = y_aux;
    zoom = zoom_aux;
}

PosTeleAssio::PosTeleAssio(const PosTeleAssio& orig):PosTeleXY(orig.x, orig.y) {
    zoom = orig.zoom;
}
