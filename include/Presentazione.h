/* 
 * File:   Presentazione.h
 * Author: tonegas
 *
 * Created on 11 dicembre 2009, 16.08
 */

#ifndef _PRESENTAZIONE_H
#define	_PRESENTAZIONE_H

class Livello;

#include "Domino.h"

class Presentazione : public Livello {
public:
    Presentazione(StrutturaLivello *livello);
    Presentazione(int num_x_colonne_aux, int num_y_righe_aux);
    Presentazione(const Presentazione& orig);
    Presentazione(const Livello& orig);
};

#endif	/* _PRESENTAZIONE_H */

