/* 
 * File:   MenuInserisciParola.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 22.46
 */

#ifndef _MENUINSERISCIPAROLA_H
#define	_MENUINSERISCIPAROLA_H

#include "Domino.h"

class MenuInserisciParola : public MenuAttivo {
    QString nuovo_nome;
public:
    MenuInserisciParola();

    void setNome(QString nuovo_nome_aux);
    void costruisciCaselle();
    void stampa();
};

#endif	/* _MENUINSERISCIPAROLA_H */

