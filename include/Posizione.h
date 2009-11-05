/* 
 * File:   Elemento.h
 * Author: tonegas
 *
 * Created on 31 ottobre 2009, 20.13
 */

#ifndef _POSIZONE_H
#define	_POSIZONE_H

#include "Domino.h"
#include "pezzi/Pezzo.h"
#include "basi/Base.h"

enum TipoElemento {
    ELEM_PEZZO, ELEM_BASE
};

class Elemento {
protected:
    int x, y;
public:

    Elemento(int x_aux, int y_aux) {
        x = x_aux;
        y = y_aux;
    }

    Elemento(const Elemento& orig) {
        x = orig.x;
        y = orig.y;
    }

    int getX()const {
        return x;
    }

    int getY()const {
        return y;
    }

    virtual void stampa(bool wire, int x, int y, GLfloat attivo) {
    }

    virtual void stampa() {
    }
    //virtual ~Elemento();
};

class ElementoAttivo {
 //   friend class Griglia;
    public:
    int x, y;

    TipoElemento tipo;
    GLfloat selezione;

    //puntatore all'oggetto Elemento pezzo o base che sia che sarà allocato quando è presente un pezzo nella casella
    //bool occupato;
    Elemento *elem;

    ElementoAttivo *next;
    ElementoAttivo *prev;



    ElementoAttivo(Elemento *elem_aux, int x_aux, int y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL) {
        x = x_aux;
        y = y_aux;
        tipo = tipo_aux;
        selezione = 0.0;
        //occupato = true;
        elem = elem_aux;
        prev = prev_aux;
        next = next_aux;
    }

    ElementoAttivo(int x_aux, int y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL) {
        x = x_aux;
        y = y_aux;
        tipo = tipo_aux;
        selezione = 1.0;
        //occupato = false;
        elem = NULL;
        prev = prev_aux;
        next = next_aux;
    }

    ~ElementoAttivo() {
        if (elem != NULL)
            delete elem;
    }

    inline int getX() const {
        return x;
    }

    inline int getY() const {
        return y;
    }

    inline int getTipo() const {
        return tipo;
    }

    inline int getOccupato() const {
        return elem!=NULL?true:false;
    }
};

#endif	/* _POSIZONE_H */

