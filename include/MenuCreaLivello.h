/* 
 * File:   MenuCreaLivello.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 22.52
 */

#ifndef _MENUCREALIVELLO_H
#define	_MENUCREALIVELLO_H

#include "Domino.h"

class MenuCreaLivello : public MenuAttivo {
    QString nuovo_nome;
    QString dim_x_nuovo_livello;
    QString dim_y_nuovo_livello;
public:
    MenuCreaLivello();
    void costruisciCaselle();
    void stampa();
};

#endif	/* _MENUCREALIVELLO_H */

