/* 
 * File:   Base.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.45
 */

#ifndef _BASE_H
#define	_BASE_H

#define LARGHEZZA_BASE 8
#define ALTEZZA_BASE 2
#define SPESSORE_BASE 8

#define ELEM_BASE 100

#include "../Domino.h"


class Base : public Elemento{
public:
    Base();
    Base(const Base& orig);
};

#endif	/* _BASE_H */

