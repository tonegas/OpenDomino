/* 
 * File:   Griglia.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.53
 */

#ifndef _GRIGLIA_H
#define	_GRIGLIA_H

#include "Domino.h"
//#include "Posizione.h"
//#include "pezzi/Pezzo.h"

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

    PosXYZoom(const PosXYZoom &orig) {
        x = orig.x;
        y = orig.y;
        zoom = orig.zoom;
    }
};

class Griglia {
    friend class Pezzo;
    PosXYZoom griglia;
public:
    ElementoAttivo *testa_elementi;
    ElementoAttivo* **matrice_elementi;
    unsigned num_y_righe;
    unsigned num_x_colonne;

    ElementoAttivo* creaElementoAttivo(int x, int y);

    void eliminaElementoAttivo(ElementoAttivo* tokill);


    Griglia(int num_x_colonne_aux, int num_y_righe_aux);

    Griglia(const Griglia& orig);

    ~Griglia();

    void setStato(int x, int y, StatoPezzo stato);

    bool getOccupato(int x, int y);

    PosXYZoom getGriglia();

    void attivaSelezione(int x, int y, TipoElemento tipo);

    void eliminaElemento(int x, int y);

    void creaElemento(int x, int y, TipoElemento tipo);

    TipoElemento getTipo(int x, int y);

    void stampa();

    void aggiornaStato();

    bool spostaElementoAttivo(int x_sorg,int y_sorg, int x_dest,int y_dest);

    //    ElementoAttivo* getPosizione(int i, int j);

    //    Pezzo& getPezzo(int i, int j);

    //    Base& getBase(int i, int j);

    void setGrigliaZoom(GLfloat zoom);

    void setGrigliaXY(GLfloat x, GLfloat y);

    unsigned getDimGrigliaX() const;

    unsigned getDimGrigliaY() const;
};

#endif	/* _GRIGLIA_H */

