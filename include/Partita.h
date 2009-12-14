/* 
 * File:   Partita.h
 * Author: tonegas
 *
 * Created on 3 novembre 2009, 0.21
 */

#ifndef _PARTITA_H
#define	_PARTITA_H

class Livello;

#include "Domino.h"

class Partita : public Livello {
protected:
    void mouseButtonDown();
    void mouseMotion();
    void attivaSelezioni();
public:
    Partita(StrutturaLivello *livello);
    Partita(int num_x_colonne_aux, int num_y_righe_aux);
    Partita(const Partita& orig);
    Partita(const Livello& orig);
};

#endif	/* _PARTITA_H */

