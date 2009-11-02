/* 
 * File:   Partita.cpp
 * Author: tonegas
 * 
 * Created on 3 novembre 2009, 0.21
 */

#include "../include/Partita.h"
#include "../include/Gioco.h"

Partita::Partita(int num_y_righe_aux, int num_x_colonne_aux) : Livello(num_x_colonne_aux, num_y_righe_aux, FRAMERATE) {
}

Partita::Partita(const Partita& orig):Livello(orig){}

//Partita::~Partita() {
//}

