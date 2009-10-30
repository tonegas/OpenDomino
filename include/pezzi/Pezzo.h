/* 
 * File:   Pezzo.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.35
 */

#ifndef _PEZZO_H
#define	_PEZZO_H

#define LARGHEZZA_PEZZO 4
#define ALTEZZA_PEZZO 8
#define SPESSORE_PEZZO 2

#include "../Domino.h"

class Pezzo {
    bool presente;
    GLfloat selezione;
public:

    Pezzo(bool alive_aux = false);

    Pezzo(const Pezzo& orig);

    void setAlive(bool alive_aux);

    bool getAlive();

    void setSelezione(GLfloat selezione_aux);

    GLfloat getSelezione();
};

#endif	/* _PEZZO_H */

