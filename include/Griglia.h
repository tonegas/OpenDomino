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
    bool in_partita;
    ElementoAttivo *testa_elementi;
    ElementoAttivo* **matrice_elementi;
    unsigned num_y_righe;
    unsigned num_x_colonne;

    ElementoAttivo* creaElementoAttivo(unsigned x, unsigned y);

    void eliminaElementoAttivo(ElementoAttivo* tokill);


    Griglia(unsigned num_x_colonne_aux, unsigned num_y_righe_aux);

    Griglia(const Griglia& orig);

    ~Griglia();

    bool setStato(unsigned x, unsigned y, StatoPezzo stato);

    bool getOccupato(unsigned x, unsigned y);

    PosXYZoom getGriglia();

    bool attivaSelezione(unsigned x, unsigned y, TipoElemento tipo);

    bool eliminaElemento(unsigned x, unsigned y);

    bool creaElemento(unsigned x, unsigned y, TipoElemento tipo);

    TipoElemento getTipo(unsigned x, unsigned y);

    bool spostaElementoAttivo(unsigned x_sorg, unsigned y_sorg, unsigned x_dest, unsigned y_dest);

    //    ElementoAttivo* getPosizione(int i, int j);

    //    Pezzo& getPezzo(int i, int j);

    //    Base& getBase(int i, int j);

    void setInPartita(bool aux_in_partita);

    void setGrigliaZoom(GLfloat zoom);

    void setGrigliaXY(GLfloat x, GLfloat y);

    unsigned getDimGrigliaX() const;

    unsigned getDimGrigliaY() const;


    void stampa();

    void aggiornaStato();

    void aggiornaStatoEStampa();
};

#endif	/* _GRIGLIA_H */

