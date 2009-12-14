/* 
 * File:   Presentazione.cpp
 * Author: tonegas
 * 
 * Created on 11 dicembre 2009, 16.08
 */

#include "../include/Domino.h"

Presentazione::Presentazione(StrutturaLivello *livello) : Livello(livello,LIVELLO_PRESENTAZIONE) {
    griglia_livello->setInPartita(true);
}

Presentazione::Presentazione(int num_x_colonne_aux, int num_y_righe_aux)
: Livello(num_x_colonne_aux, num_y_righe_aux, LIVELLO_PRESENTAZIONE) {
    griglia_livello->setInPartita(true);
}

Presentazione::Presentazione(const Presentazione& orig) : Livello(orig) {
    griglia_livello->setInPartita(true);
}

Presentazione::Presentazione(const Livello& orig) : Livello(orig) {
    griglia_livello->setInPartita(true);
}
