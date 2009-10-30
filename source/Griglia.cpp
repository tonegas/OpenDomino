/* 
 * File:   Griglia.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.53
 */

#include "../include/Domino.h"

Griglia::Griglia(int num_x_colonne_aux, int num_y_righe_aux) {
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    matrice_pezzi = new Pezzo*[num_x_colonne];
    matrice_basi = new Base*[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_pezzi[i] = new Pezzo[num_y_righe];
        matrice_basi[i] = new Base[num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++)
        for (unsigned j = 0; j < num_y_righe; j++) {
            matrice_pezzi[i][j].setAlive(false);
            matrice_basi[i][j].setAlive(false);
        }
}

Griglia::Griglia(const Griglia& orig) {
    griglia = orig.griglia;
    num_y_righe = orig.num_y_righe;
    num_x_colonne = orig.num_x_colonne;
    matrice_pezzi = new Pezzo*[num_x_colonne];
    matrice_basi = new Base*[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_pezzi[i] = new Pezzo[num_y_righe];
        matrice_basi[i] = new Base[num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++)
        for (unsigned j = 0; j < num_y_righe; j++) {
            matrice_pezzi[i][j].setAlive(orig.matrice_pezzi[i][j].getAlive());
            matrice_basi[i][j].setAlive(orig.matrice_basi[i][j].getAlive());
        }
}

Griglia::~Griglia() {
    for (unsigned i = 0; i < num_x_colonne; i++) {
        delete matrice_pezzi[i];
        delete matrice_basi[i];
    }
    delete matrice_pezzi;
    delete matrice_basi;
}

PosXYZoom Griglia::getGriglia() {
    return griglia;
}

Pezzo& Griglia::getPezzo(int i, int j) {
    return matrice_pezzi[i][j];
}

Base& Griglia::getBase(int i, int j) {
    return matrice_basi[i][j];
}

void Griglia::setGrigliaZoom(GLfloat zoom) {
    griglia.zoom = zoom;
}

void Griglia::setGrigliaXY(GLfloat x, GLfloat y) {
    griglia.x = x;
    griglia.y = y;
}

unsigned Griglia::getDimGrigliaX() {
    return num_x_colonne;
}

unsigned Griglia::getDimGrigliaY() {
    return num_y_righe;
}
