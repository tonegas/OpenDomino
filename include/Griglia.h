/* 
 * File:   Griglia.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.53
 */

#ifndef _GRIGLIA_H
#define	_GRIGLIA_H

#include "Domino.h"

class Griglia {
    friend class Pezzo;

public:
    bool in_partita;
    ElementoAttivo *testa_elementi;
    ElementoAttivo* **matrice_elementi;
    unsigned num_y_righe;
    unsigned num_x_colonne;

    ElementoAttivo* creaElementoAttivo(unsigned x, unsigned y);
    void eliminaElementoAttivo(ElementoAttivo* tokill);

//public:

    Griglia(unsigned num_x_colonne_aux, unsigned num_y_righe_aux);

    Griglia(const Griglia& orig);

    ~Griglia();

    bool setStato(unsigned x, unsigned y, StatoPezzo stato);

    bool getOccupato(unsigned x, unsigned y);

    bool attivaSelezione(unsigned x, unsigned y, TipoElemento tipo);

    bool eliminaElemento(unsigned x, unsigned y);

    bool creaElemento(unsigned x, unsigned y, TipoElemento tipo);

    TipoElemento getTipo(unsigned x, unsigned y);

    ElementoAttivo* getTestaElementi() const;

    bool spostaElementoAttivo(unsigned x_sorg, unsigned y_sorg, unsigned x_dest, unsigned y_dest);

    void setInPartita(bool aux_in_partita);

    bool getInPartita();

    unsigned getDimGrigliaX() const;

    unsigned getDimGrigliaY() const;

    void stampa();

    void aggiornaStato();

    void aggiornaStatoEStampa();
};

#endif	/* _GRIGLIA_H */

