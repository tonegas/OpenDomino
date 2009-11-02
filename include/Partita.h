/* 
 * File:   Partita.h
 * Author: tonegas
 *
 * Created on 3 novembre 2009, 0.21
 */

#ifndef _PARTITA_H
#define	_PARTITA_H

#include "Domino.h"
#include "Livello.h"

class Partita :public Livello{
public:
    Partita(int num_y_righe_aux = GRIGLIA_EDITOR_Y, int num_x_colonne_aux = GRIGLIA_EDITOR_X);
    Partita(const Partita& orig);
    //virtual ~Partita();
private:

};

#endif	/* _PARTITA_H */

