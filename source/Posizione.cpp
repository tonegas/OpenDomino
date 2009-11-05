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
        occupata = false;
        elem_lista = NULL;
    }

    Posizione::~Posizione() {
//        delete elem;
        elem_lista = NULL;
    }

    Elemento* Posizione::getElem(){
        return elem_lista;
    }

    void Posizione::liberaPosizione() {
//        delete elem;
        occupata = 0;
        elem_lista = NULL;
    }

//    void Posizione::attivaSelezione(int tipo_aux) {
//        if (tipo_aux == ELEM_PEZZO)
//            selezione_pezzo = 1;
//        if (tipo_aux == ELEM_BASE)
//            selezione_base = 1;
//    }

//    int Posizione::getTipo() {
//        return tipo;
//    }

    void Posizione::occupaPosizione(ElementoLista *elem_aux) {
        occupata = true;
        elem_lista = elem_aux;
    }
