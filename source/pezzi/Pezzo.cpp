/* 
 * File:   Pezzo.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.35
 */

#include "../../include/pezzi/Pezzo.h"

Pezzo::Pezzo(bool alive_aux) {
    presente = alive_aux;
}

Pezzo::Pezzo(const Pezzo& orig) {
    presente = orig.presente;
    selezione = orig.selezione;
}

void Pezzo::setAlive(bool alive_aux) {
    presente = alive_aux;
}

bool Pezzo::getAlive() {
    return presente;
}

void Pezzo::setSelezione(GLfloat selezione_aux) {
    selezione = selezione_aux;
}

GLfloat Pezzo::getSelezione() {
    return selezione;
}
