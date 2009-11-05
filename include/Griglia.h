/* 
 * File:   Griglia.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.53
 */

#ifndef _GRIGLIA_H
#define	_GRIGLIA_H

#include "Domino.h"
#include "pezzi/Pezzo.h"
#include "basi/Base.h"

class PosXYZoom {
public:
    GLfloat x;
    GLfloat y;
    GLfloat zoom;

    PosXYZoom(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 1) {
        x = x_aux;
        y = y_aux;
        zoom = zoom_aux;
    }

    PosXYZoom(const PosXYZoom &orig) {
        x = orig.x;
        y = orig.y;
        zoom = orig.zoom;
    }

    //    inline GLfloat getX() const {
    //        return x;
    //    }
};

class Griglia {
    PosXYZoom griglia;
    //la cosa migliore è creare un unico oggetto che implementa sia lista che matrice
    //Doppia struttura di memorizzazione
    ElementoAttivo* **matrice_elementi;
    ElementoAttivo *testa_elementi;
    unsigned num_y_righe;
    unsigned num_x_colonne;

    void inserisci(Elemento *elem, int x, int y,TipoElemento tipo);

    void inserisci(int x,int y,TipoElemento tipo);

    void inserisci(Elemento *elem, ElementoAttivo *elem_lista);

    void estrazione(ElementoAttivo *elem_lista);
public:
    Griglia(int num_x_colonne_aux, int num_y_righe_aux);

    ~Griglia();

    void pulisciGriglia();

    void inserisciElemento(Elemento *elem, int x, int y, TipoElemento tipo);

    Griglia(const Griglia& orig);


    

    void attivaSelezione(int x, int y, int tipo);

    GLfloat getSelezione(int x, int y);

    void aggiornaSelezione(int x,int y);

    void liberaPosizione(int x, int y);

    void occupaPosizione(int x, int y, int tipo, bool selezione = false);

    bool getOccupata(int x, int y);

    int getTipo(int x, int y);

    //    Posizione* getPosizione(int i, int j);
    //
    //    Pezzo& getPezzo(int i, int j);
    //
    //    Base& getBase(int i, int j);

    PosXYZoom getGriglia();

    void setGrigliaZoom(GLfloat zoom);

    void setGrigliaXY(GLfloat x, GLfloat y);

    unsigned getDimGrigliaX() const;

    unsigned getDimGrigliaY() const;
};

#endif	/* _GRIGLIA_H */

