/* 
 * File:   Griglia.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.53
 */

#include "../include/Griglia.h"

Griglia::Griglia(int num_x_colonne_aux, int num_y_righe_aux) {
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    matrice_posizioni = new Posizione *[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_posizioni[i] = new Posizione[num_y_righe];
    }
}

Griglia::Griglia(const Griglia& orig) {
    griglia = orig.griglia;
    num_y_righe = orig.num_y_righe;
    num_x_colonne = orig.num_x_colonne;
    matrice_posizioni = new Posizione *[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_posizioni[i] = new Posizione[num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            if (orig.matrice_posizioni[i][j].occupata == true) {
                if (orig.matrice_posizioni[i][j].tipo == ELEM_PEZZO) {
                    matrice_posizioni[i][j].occupaPosizione(new Pezzo(i, j), ELEM_PEZZO);
                } else {
                    matrice_posizioni[i][j].occupaPosizione(new Base(i, j), ELEM_BASE);
                }
            }
        }
    }
}

Griglia::~Griglia() {
    for (unsigned i = 0; i < num_x_colonne; i++) {
        delete [] matrice_posizioni[i];
    }
    delete [] matrice_posizioni;
}

PosXYZoom Griglia::getGriglia() {
    return griglia;
}

Posizione* Griglia::getPosizione(int i, int j){
    return &matrice_posizioni[i][j];
}

Pezzo& Griglia::getPezzo(int i, int j) {
    return *(Pezzo*)matrice_posizioni[i][j].elem;
}

Base& Griglia::getBase(int i, int j) {
    return *(Base*)matrice_posizioni[i][j].elem;
}

void Griglia::setGrigliaZoom(GLfloat zoom) {
    griglia.zoom = zoom;
}

void Griglia::setGrigliaXY(GLfloat x, GLfloat y) {
    griglia.x = x;
    griglia.y = y;
}

unsigned Griglia::getDimGrigliaX() const{
    return num_x_colonne;
}

unsigned Griglia::getDimGrigliaY() const{
    return num_y_righe;
}
