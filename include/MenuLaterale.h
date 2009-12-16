/* 
 * File:   MenuLaterale.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 18.43
 */

#ifndef _MENULATERALE_H
#define	_MENULATERALE_H

#include "Domino.h"

class MenuLaterale : public MenuAttivo {
    int dist_da_sinistra, dist_da_basso_voce_uscita;
    QVector<float> trasparenza_voci_visibili;
public:
    MenuLaterale();

    QString getStringa();
    void resizeAggiuntivo();
    void costruisciCaselle();
    void stampa();
    void aggiornaMovimento();
    void aggiornaMovimento(unsigned pos_mouse_x, unsigned pos_mouse_y);
    bool gestisciSelezioneMouse(unsigned pos_mouse_x, unsigned pos_mouse_y);
};

#endif	/* _MENULATERALE_H */

