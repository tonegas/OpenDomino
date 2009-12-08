/* 
 * File:   TelecameraAssionometrica.h
 * Author: tonegas
 *
 * Created on 14 novembre 2009, 23.34
 */

#ifndef _TELECAMERAASSIONOMETRICA_H
#define	_TELECAMERAASSIONOMETRICA_H

#define ASSIONOMETRICA_ZOOM_MAX 23
#define ASSIONOMETRICA_ZOOM_MIN 0.25
#define ASSIONOMETRICA_DELTA_ZOOM 1.1
#define ASSIONOMETRICA_INCREMENTO_DELTA_ZOOM 1.1
#define ASSIONOMETRICA_ZFAR 20000
#define ASSIONOMETRICA_ZNEAR 1
#define ASSIONOMETRICA_Z_TELECAMERA 200
#define ASSIONOMETRICA_Y_TELECAMERA -400
#define ASSIONOMETRICA_X_TELECAMERA -400

#include "Domino.h"

class TelecameraAssionometrica : public Telecamera {
    PosTeleAssio posizione_telecamera_iniziale;
    PosTeleAssio posizione_telecamera;

    //posizione 3d iniziali del mouse per lo spostamento della griglia
    GLdouble pos_x_iniziale, pos_y_iniziale; //questi si inizializzano da soli quando premo

    //flag che indica se è incorso un animazione sullo zoom
    bool mouvi_zoom; //inizializzati nella setProiezione
    //massimo livello di zoom per la proiezione corrente
    GLfloat max_zoom, min_zoom; //inizializzati nella setProiezione
    //variazione del delta di incremento dello zoom
    GLfloat delta_zoom; //ok
    //tempo per il reset del delta_zoom
    int tempo_reset_delta_zoom; //ok
public:

    TelecameraAssionometrica(unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux);

    TelecameraAssionometrica(const TelecameraAssionometrica& orig);

    TelecameraAssionometrica(PosTeleAssio &pos_tele_aux, unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux);

    void setProiezioneTelecamera(int larghezza_fin, int altezza_fin);

    bool getMousePosGrigliaXY();

    bool mouseSelezione(Livello *liv, Griglia* griglia_livello);

    void registraPosizione();

    void registraZoomAvanti();

    void registraZoomIndietro();

    void cambiaXY();

    void animaZoom();

    void controlloPosizione();

    void resettaDeltaZoom(int frame_ms);

    void visualeOpenGL();

    void configuraVisuale();

    PosTeleAssio* getPosTeleAssio();
};

#endif	/* _TELECAMERAASSIONOMETRICA_H */

