/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 31 ottobre 2009, 20.13
 */

#include "../include/Domino.h"

Elemento::Elemento(int tipo_aux,bool alive_aux) {
    presente = alive_aux;
    tipo = tipo_aux;
}

Elemento::Elemento(const Elemento& orig) {
    presente = orig.presente;
    selezione = orig.selezione;
}

void Elemento::setAlive(bool alive_aux) {
    presente = alive_aux;
}

bool Elemento::getAlive() {
    return presente;
}

int Elemento::getTipo() {
    return tipo;
}

void Elemento::setSelezione(GLfloat selezione_aux) {
    selezione = selezione_aux;
}

GLfloat Elemento::getSelezione() {
    return selezione;
}
