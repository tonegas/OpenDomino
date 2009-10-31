/* 
 * File:   Pezzo.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.35
 */

#include "../../include/Domino.h"

Pezzo::Pezzo(bool alive_aux):Elemento(PEZZ0_GIALLO,alive_aux) {}

Pezzo::Pezzo(const Pezzo& orig) : Elemento(orig) {}