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
    matrice_elementi = new Elemento**[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_elementi[i] = new Elemento*[num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            matrice_elementi[i][j] = NULL;
        }
    }
}

Griglia::Griglia(const Griglia& orig) {
    griglia = orig.griglia;
    num_y_righe = orig.num_y_righe;
    num_x_colonne = orig.num_x_colonne;
    matrice_elementi = new Elemento**[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_elementi[i] = new Elemento*[num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            if (orig.matrice_elementi[i][j] != NULL) {
                if (orig.matrice_elementi[i][j]->getTipo() == 1) {
                    matrice_elementi[i][j] = new Pezzo(*(Pezzo*)orig.matrice_elementi[i][j]);
                } else {
                    matrice_elementi[i][j] = new Base(*(Base*)orig.matrice_elementi[i][j]);
                }
            }
        }
    }
}

Griglia::~Griglia() {
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            delete matrice_elementi[i][j];
        }
    }
    for (unsigned i = 0; i < num_x_colonne; i++) {
        delete (*matrice_elementi)[i];
    }
    delete matrice_elementi;
}

PosXYZoom Griglia::getGriglia() {
    return griglia;
}

Pezzo& Griglia::getPezzo(int i, int j) {
    return *(Pezzo*)matrice_elementi[i][j];
}

Base& Griglia::getBase(int i, int j) {
    return *(Base*)matrice_elementi[i][j];
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
