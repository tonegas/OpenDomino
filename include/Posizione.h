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

class Elemento {
protected:
    GLfloat selezione;
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

    void attivaSelezione(){
        selezione = 1;
    }

    GLfloat getSelezione(){
        return selezione;
    }

    virtual void stampa(bool wire, int x, int y, GLfloat attivo) {
    }

    virtual void stampa() {
    }
    //virtual ~Elemento();
};

class ElementoLista {
public:
    int tipo;
    ElementoLista *next;
    ElementoLista *prev;
    Elemento *elem;

    ElementoLista(Elemento *elem_aux, int tipo_aux, ElementoLista *next_aux = NULL, ElementoLista *prev_aux = NULL) {
        elem = elem_aux;
        prev = prev_aux;
        next = next_aux;
        tipo = tipo_aux;
    }

    ElementoLista(int x, int y, int tipo_aux) {
        tipo = tipo_aux;
        switch (tipo) {
//            case ELEM_PEZZO:
//                elem = new Pezzo(x, y);
//                break;
//            case ELEM_BASE:
//                elem = new Base(x, y);
//                break;
        }
    }

    ~ElementoLista() {
        delete elem;
    }
};

class Posizione {
public:
    bool occupata;
    ElementoLista *elem_lista;

    Posizione();

    ~Posizione();

    ElementoLista* getElem();

    void liberaPosizione();

    //  void attivaSelezione(int tipo_aux);

    //    int getTipo();

    void occupaPosizione(ElementoLista *elem_aux);
};

#endif	/* _POSIZONE_H */

