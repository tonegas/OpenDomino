/* 
 * File:   Griglia.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.53
 */

#ifndef _GRIGLIA_H
#define	_GRIGLIA_H

#include "Domino.h"

class PosXYZoom {
public:
    GLfloat x;
    GLfloat y;
    GLfloat zoom;

    PosXYZoom(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 1) {
        x = x_aux;
        y = y_aux;
        zoom = zoom_aux;
    }
};

class Griglia {
    PosXYZoom griglia;
    Pezzo **matrice_pezzi;
    Base **matrice_basi;
    unsigned num_y_righe;
    unsigned num_x_colonne;
public:

    Griglia(int num_x_colonne_aux, int num_y_righe_aux);

    Griglia(const Griglia& orig);

    ~Griglia();

    PosXYZoom getGriglia();

    Pezzo& getPezzo(int i, int j);

    Base& getBase(int i, int j);

    void setGrigliaZoom(GLfloat zoom);

    void setGrigliaXY(GLfloat x, GLfloat y);

    unsigned getDimGrigliaX();

    unsigned getDimGrigliaY();
};

#endif	/* _GRIGLIA_H */

