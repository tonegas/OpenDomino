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
//#include "Livello.h"

class Partita :public Livello{
public:
    Partita(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux);
    Partita(const Partita& orig);
    Partita(const Livello& orig);
//    int aggiornaStato();
//    int gestisciInput(SDL_Event *evento);
//    int video();

    void mouseButtonDown(SDL_Event *evento);
    void mouseMotion(SDL_Event *evento);
    void attivaSelezioni();
    //virtual ~Partita();
};

#endif	/* _PARTITA_H */

