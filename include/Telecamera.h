/* 
 * File:   Telecamera.h
 * Author: tonegas
 *
 * Created on 14 novembre 2009, 23.31
 */

#ifndef _TELECAMERA_H
#define	_TELECAMERA_H

class Livello;

class PosTeleXY {
protected:
public:
    GLfloat x;
    GLfloat y;

    PosTeleXY(GLfloat x_aux = 0, GLfloat y_aux = 0) {
        x = x_aux;
        y = y_aux;
    }

    PosTeleXY(const PosTeleXY &orig) {
        x = orig.x;
        y = orig.y;
    }
};

class PosTeleProsp : public PosTeleXY {
public:
    GLfloat z;
    GLfloat ang_x;
    GLfloat ang_y;

    PosTeleProsp(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat z_aux = 1, GLfloat ang_x_aux = 0, GLfloat ang_y_aux = 0) {
        x = x_aux;
        y = y_aux;
        z = z_aux;
        ang_x = ang_x_aux;
        ang_x = ang_y_aux;
    }

    PosTeleProsp(const PosTeleProsp& orig) {
        x = orig.x;
        y = orig.y;
        z = orig.z;
        ang_x = orig.ang_x;
        ang_x = orig.ang_y;
    }
};

class PosTeleAssio : public PosTeleXY {
public:
    GLfloat zoom;

    PosTeleAssio(GLfloat x_aux = 0, GLfloat y_aux = 0, GLfloat zoom_aux = 1) {
        x = x_aux;
        y = y_aux;
        zoom = zoom_aux;
    }

    PosTeleAssio(const PosTeleAssio& orig) {
        x = orig.x;
        y = orig.y;
        zoom = orig.zoom;
    }
};

//calsse per il salvataggio delle telecamere

class PosTelecamere {
public:
    PosTeleProsp telecamera_prospettica;
    PosTeleAssio telecamera_assionometrica;
};

#include "Domino.h"

class Telecamera {
protected:
    //dimensione griglia su cui la telecamera lavora
    unsigned dim_grilia_X, dim_grilia_Y;
    
    //matrici per il recupero dell'input del muose
    //inizializzate della classe che deriva livello
    GLdouble matrice_model[16]; //inizializzati nella setProiezione
    //coordinate sono riferite alla griglia
    GLdouble matrice_model_griglia[16]; //inizializzata dalla funzione video
    GLdouble matrice_proj[16]; //inizializzati nella setProiezione
    GLint matrice_view[4]; //inizializzati nella setProiezione

    //questi li tocca solo livello
    //-----------------------------------------
    //posizione 2d del mouse sulla finestra
    //posizione z della superfice base di sfondo dove cammina il mouse
    GLdouble mouse_z_fin_double; //inizializzati nella setProiezione
    int mouse_x_fin, mouse_y_fin; //si inizializzano nella getMousePosGrigliaXY
    //-----------------------------------------

public:

    //questi li possono usare livello ma anche le classi derivate
    //----------------------------------
    //variabili per il posizionamento del mouse nello spazio 3d
    //posizione 3d del mouse assolute
    GLdouble pos_x, pos_y, pos_z; //si inizializzano nella getMousePosGrigliaXY
    //posizione 3d del mouse rispetto alla griglia
    GLdouble pos_x_griglia, pos_y_griglia, pos_z_griglia;
    //indice sulla griglia del mouse
    unsigned indice_x_griglia, indice_y_griglia; //si inizializzano nella getMousePosGrigliaXY
    //indicatore booleano che indica se l'indice sulla griglia è più o meno sensato
    bool indice_griglia_ok; //si inizializzano nella getMousePosGrigliaXY
    //---------------------------------

    //    //questi li possono usare livello ma anche le classi derivate
    //    //---------------------------
    //    //variabili per la selezione dei pezzi
    //    Selezione caratteristiche_selezione;
    //    //flag che indica se ho selezionato sia
    //    bool entrambi;
    //    unsigned x_pezzo_selezionato, y_pezzo_selezionato;
    //    unsigned x_base_selezionata, y_base_selezionata;
    //---------------------------

    Telecamera(unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux);

    Telecamera(const Telecamera& orig);

    virtual void setProiezioneTelecamera(int larghezza_fin, int altezza_fin) = 0;

    virtual bool getMousePosGrigliaXY(int mouse_x_fin_aux, int mouse_y_fin_aux);

    virtual bool getMousePosGrigliaXY() = 0;

    virtual bool mouseSelezione(Livello *liv, Griglia* griglia_livello) = 0;

    virtual void registraPosizione() = 0;

    virtual void registraZoomAvanti() = 0;

    virtual void registraZoomIndietro() = 0;

    virtual void cambiaXY() = 0;

    virtual void cambiaAngolazione(){}

    virtual void aggiorna( int frame_ms);

    virtual void animaZoom() = 0;

    virtual void controlloPosizione() = 0;

    virtual void resettaDeltaZoom(int frame_ms) = 0;

    virtual void visualeOpenGL() = 0;
};

#endif	/* _TELECAMERA_H */

