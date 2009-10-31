/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 31 ottobre 2009, 20.13
 */

#include "../include/Domino.h"

    Posizione::Posizione() {
        selezione_pezzo = 0;
        selezione_base = 0;
        occupata = false;
        elem = NULL;
    }

    Posizione::~Posizione() {
        delete elem;
    }

    void Posizione::liberaPosizione() {
        delete elem;
        occupata = 0;
        elem = NULL;
    }

    void Posizione::attivaSelezione(int tipo_aux) {
        tipo = tipo_aux;
        if (tipo == ELEM_PEZZ0)
            selezione_pezzo = 1;
        if (tipo == ELEM_BASE)
            selezione_base = 1;
    }

    int Posizione::getTipo() {
        return tipo;
    }

    void Posizione::occupaPosizione(Elemento *elem_aux) {
        occupata = true;
        elem = elem_aux;
    }
