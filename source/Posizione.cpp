/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 31 ottobre 2009, 20.13
 */

#include "../include/Domino.h"
#include "../include/Posizione.h"
#include "../include/pezzi/Pezzo.h"
#include "../include/basi/Base.h"

    Posizione::Posizione() {
        selezione_pezzo = 0;
        selezione_base = 0;
        occupata = false;
        elem = NULL;
    }

    Posizione::~Posizione() {
        delete elem;
        elem = NULL;
    }

    Elemento* Posizione::getElem(){
        return elem;
    }

    void Posizione::liberaPosizione() {
        delete elem;
        occupata = 0;
        elem = NULL;
    }

    void Posizione::attivaSelezione(int tipo_aux) {
        if (tipo_aux == ELEM_PEZZO)
            selezione_pezzo = 1;
        if (tipo_aux == ELEM_BASE)
            selezione_base = 1;
    }

    int Posizione::getTipo() {
        return tipo;
    }

    void Posizione::occupaPosizione(Elemento *elem_aux,int tipo_aux) {
        occupata = true;
        tipo = tipo_aux;
        elem = elem_aux;
    }
