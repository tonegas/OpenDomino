/* 
 * File:   Giocatore.h
 * Author: tonegas
 *
 * Created on 12 novembre 2009, 0.04
 */

#ifndef _GIOCATORE_H
#define	_GIOCATORE_H

#include "Domino.h"


class Giocatore {
    string nome;
    fstream file_giocatore;
    //vector<CaratteristicheLivello> lista_livelli;
    time_t tempo_di_gioco_apertura;
    time_t tempo_partita;
    time_t creazione_giocatore;
public:
    Giocatore(string nome_aux);
    ~Giocatore();
    void caricaGiocatore();
    void salvaGiocatore();
    void nuovoGiocatore();
    //    Giocatore(const Giocatore& orig);
};

#endif	/* _GIOCATORE_H */

