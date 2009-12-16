/* 
 * File:   MenuCreaLivello.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 22.52
 */

#ifndef _MENUVOCIDINAMICHE_H
#define	_MENUVOCIDINAMICHE_H

#include "Domino.h"

class MenuVociDinamiche : public MenuAttivo {
public:
    MenuVociDinamiche();
    void costruisciCaselle();
    void stampa();
};

#endif	/* _MENUCREALIVELLO_H */

