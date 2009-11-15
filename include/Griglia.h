/* 
 * File:   Griglia.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.53
 */

#ifndef _GRIGLIA_H
#define	_GRIGLIA_H

#include "Domino.h"

class PosTeleXY {
protected:
public:
    GLfloat x;
    GLfloat y;

    PosTeleXY(GLfloat x_aux = 0, GLfloat y_aux = 0) {
        x = x_aux;
        y = y_aux;
    }

    PosTeleXY(const PosTeleXY &orig) {
        x = orig.x;
        y = orig.y;
    }
};

class PosTeleProsp : public PosTeleXY {
public:
    GLfloat z;
    GLfloat ang_x;
    GLfloat ang_y;

    PosTeleProsp(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat z_aux = 1, GLfloat ang_x_aux = 0, GLfloat ang_y_aux = 0) {
        x = x_aux;
        y = y_aux;
        z = z_aux;
        ang_x = ang_x_aux;
        ang_x = ang_y_aux;
    }

    PosTeleProsp(const PosTeleProsp& orig) {
        x = orig.x;
        y = orig.y;
        z = orig.z;
        ang_x = orig.ang_x;
        ang_x = orig.ang_y;
    }
};

class PosTeleAssio : public PosTeleXY {
public:
    GLfloat zoom;

    PosTeleAssio(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 1) {
        x = x_aux;
        y = y_aux;
        zoom = zoom_aux;
    }

    PosTeleAssio(const PosTeleAssio& orig) {
        x = orig.x;
        y = orig.y;
        zoom = orig.zoom;
    }
};

//calsse per il salvataggio delle telecamere

class PosTelecamere {
public:
    PosTeleProsp telecamera_prospettica;
    PosTeleAssio telecamera_assionometrica;
};

class PosXYZeZoom {
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat zoom;

    PosXYZeZoom(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat z_aux = 0, GLfloat zoom_aux = 1) {
        x = x_aux;
        y = y_aux;
        z = z_aux;
        zoom = zoom_aux;
    }

    PosXYZeZoom(const PosXYZeZoom &orig) {
        x = orig.x;
        y = orig.y;
        z = orig.z;
        zoom = orig.zoom;
    }
};

class Griglia {
    friend class Pezzo;

    //la posizione della griglia sparirà di qui e andrà tutta contrentrata sull'utilizzo delle telecamere
    //dentro il livello
    PosXYZeZoom griglia;

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

    PosXYZeZoom getGriglia();

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

    void setGrigliaZ(GLfloat z);

    void setGrigliaXY(GLfloat x, GLfloat y);

    unsigned getDimGrigliaX() const;

    unsigned getDimGrigliaY() const;

    void stampa();

    void aggiornaStato();

    void aggiornaStatoEStampa();
};

#endif	/* _GRIGLIA_H */

