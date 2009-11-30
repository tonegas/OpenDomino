/* 
 * File:   PosTelecamere.h
 * Author: tonegas
 *
 * Created on 30 novembre 2009, 15.38
 */

#ifndef _POSTELECAMERE_H
#define	_POSTELECAMERE_H

#include "Domino.h"

class PosTeleXY {
protected:
public:
    GLfloat x;
    GLfloat y;

    PosTeleXY(GLfloat x_aux = 0, GLfloat y_aux = 0);

    PosTeleXY(const PosTeleXY &orig);
};

class PosTeleProsp : public PosTeleXY {
public:
    GLfloat z;
    GLfloat ang_x;
    GLfloat ang_y;

    PosTeleProsp(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat z_aux = 0, GLfloat ang_x_aux = 0, GLfloat ang_y_aux = 0);

    PosTeleProsp(const PosTeleProsp& orig);
};

class PosTeleAssio : public PosTeleXY {
public:
    GLfloat zoom;

    PosTeleAssio(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 1);

    PosTeleAssio(const PosTeleAssio& orig);
};

//calsse per il salvataggio delle telecamere

class PosTelecamere {
public:
    PosTeleProsp telecamera_prospettica;
    PosTeleAssio telecamera_assionometrica;
};

#endif	/* _POSTELECAMERE_H */

