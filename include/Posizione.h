/* 
 * File:   Elemento.h
 * Author: tonegas
 *
 * Created on 31 ottobre 2009, 20.13
 */

#ifndef _POSIZONE_H
#define	_POSIZONE_H

#include "Domino.h"

enum TipoElemento {
    NESSUNO, ELEM_PEZZO, ELEM_BASE
};

class Elemento {
protected:
    int x, y;
public:

    Elemento(int x_aux, int y_aux) {
        x = x_aux;
        y = y_aux;
    };

    Elemento(const Elemento& orig) {
        x = orig.x;
        y = orig.y;
    };

    virtual Elemento* costruttore(){
        return NULL;
    }

    virtual void aggiornaStato(){}

    virtual void setStato(void *stato){}

    static void stampa(bool wire, int x, int y, GLfloat attivo) {
    }

    virtual void stampa() {
    }
    //virtual ~Elemento();
};

class ElementoAttivo {
    friend class Griglia;
public:
    int x, y;
    TipoElemento tipo;
    Elemento *elem;

    GLfloat selezione_pezzo;
    GLfloat selezione_base;
    ElementoAttivo *next;
    ElementoAttivo *prev;


    ElementoAttivo();

    ElementoAttivo(int x_aux, int y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL);

    ElementoAttivo(Elemento *elem_aux, int x_aux, int y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL);

    ElementoAttivo(int x_aux, int y_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL);

    ElementoAttivo(const ElementoAttivo& orig);

    ~ElementoAttivo();

    Elemento* getElem();

    void liberaPosizione();

    void attivaSelezione(int tipo_aux);

    bool getOccupato();

    int getTipo();

    void occupaPosizione(Elemento *elem_aux, TipoElemento tipo_aux);
};

#endif	/* _POSIZONE_H */

