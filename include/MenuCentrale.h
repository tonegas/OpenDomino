/* 
 * File:   MenuCentrale.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 18.35
 */

#ifndef _MENUCENTRALE_H
#define	_MENUCENTRALE_H

#include "Domino.h"

class MenuCentrale : public MenuAttivo {
    GLuint lista_menu;
public:
    MenuCentrale();

    void costruisciCaselle();
    void stampa();
};

#endif	/* _MENUCENTRALE_H */

