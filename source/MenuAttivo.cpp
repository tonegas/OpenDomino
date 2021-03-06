/* 
 * File:   MenuAttivo.cpp
 * Author: tonegas
 * 
 * Created on 14 dicembre 2009, 18.32
 */

#include "../include/Domino.h"

MenuAttivo::MenuAttivo() {
}

void MenuAttivo::aggiornaMovimento(unsigned pos_mouse_x, unsigned pos_mouse_y) {
    PARAMETRO_NON_USATO(pos_mouse_x),PARAMETRO_NON_USATO(pos_mouse_y);
}

void MenuAttivo::setCarattere(FTPixmapFont *font_aux, FTSimpleLayout *layout_aux) {
    font = font_aux;
    layout = layout_aux;
}

void MenuAttivo::inserisci(QString voce, StatoMenu stato, bool attivo, bool selezionabile) {
    if (titolo.isEmpty()) {
        titolo = voce;
    } else {
        voci_menu += voce;
        stati_menu += stato;
        voci_dinamiche += NULL;
        stati_menu_attivi += attivo;
        stati_menu_selezionabili += selezionabile;
        stato_attivo_voci_menu += 0;
    }
    numero_voci_menu_attivo = voci_menu.count();
}

void MenuAttivo::inserisci(QStringList lista_voci, StatoMenu stato) {
    voci_menu += lista_voci;
    stati_menu.fill(stato, lista_voci.count());
    stati_menu_attivi.fill(true, lista_voci.count());
    voci_dinamiche.fill(NULL, lista_voci.count());
    stati_menu_selezionabili.fill(true, lista_voci.count());
    stato_attivo_voci_menu.fill(false, lista_voci.count());
    numero_voci_menu_attivo = voci_menu.count();
}

void MenuAttivo::inserisci(QString parte_iniziale_voce, QString* voce_dinamica, StatoMenu stato, bool selezionabile) {
    voci_menu += parte_iniziale_voce;
    stati_menu += stato;
    stati_menu_attivi += true;
    voci_dinamiche += voce_dinamica;
    stati_menu_selezionabili += selezionabile;
    stato_attivo_voci_menu += 0;
    numero_voci_menu_attivo = voci_menu.count();
}

void MenuAttivo::azzera() {
    voce_selezionata = 0;
    numero_voci_menu_attivo = 0;
    titolo.clear();
    voci_menu.clear();
    stati_menu.clear();
    voci_dinamiche.clear();
    stati_menu_selezionabili.clear();
    stati_menu_attivi.clear();
    stato_attivo_voci_menu.clear();
}

StatoMenu MenuAttivo::statoSelezionato() {
    return stati_menu[voce_selezionata];
}

void MenuAttivo::incrementoSelezione() {
    do {
        voce_selezionata = (++voce_selezionata % numero_voci_menu_attivo);
    } while (!stati_menu_selezionabili[voce_selezionata]);
    aggiornaMovimento();
}

void MenuAttivo::decrementoSelezione() {
    do {
        voce_selezionata = ((voce_selezionata - 1 >= numero_voci_menu_attivo) ? numero_voci_menu_attivo - 1 : voce_selezionata - 1);
    } while (!stati_menu_selezionabili[voce_selezionata]);
    aggiornaMovimento();
}

bool MenuAttivo::gestisciSelezioneMouse(unsigned pos_mouse_x, unsigned pos_mouse_y) {
    double pos_x = (double) pos_mouse_x;
    double pos_y = dim_y_fin - (double) pos_mouse_y;
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (stati_menu_selezionabili[i]) {
            if (pos_x < posizioni_caselle_menu_attivo[i].X() + destra &&
                    pos_x > posizioni_caselle_menu_attivo[i].X() + sinistra &&
                    pos_y < posizioni_caselle_menu_attivo[i].Y() + (double) dist_da_voce / 1.8 &&
                    pos_y > posizioni_caselle_menu_attivo[i].Y() - (double) dist_da_voce / 5.2) {
                voce_selezionata = i;
                return true;
            }
        }
    }
    return false;
}

void MenuAttivo::aggiorna() {
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (i == voce_selezionata) {
            stato_attivo_voci_menu[i] = 1.0f;
        } else {
            stato_attivo_voci_menu[i] = stato_attivo_voci_menu[i] - 0.10 > 0.0 ? stato_attivo_voci_menu[i] - 0.10 : 0.0;
        }
    }
}

void MenuAttivo::resize() {
    if (dim_x_fin >= 1000 && dim_y_fin >= 1000) {
        dim_voce_principale = 65;
        dim_voce = 50;
    } else {
        if (dim_x_fin > dim_y_fin) {
            dim_voce_principale = (float) dim_y_fin / 500.0 * 32;
            dim_voce = (float) dim_y_fin / 500.0 * 25;
        } else {
            dim_voce_principale = (float) dim_x_fin / 500.0 * 32;
            dim_voce = (float) dim_x_fin / 500.0 * 25;
        }
    }
    dist_da_basso_voce_principale = (dim_y_fin / 2 + numero_voci_menu_attivo * dim_voce / 5 * 4);
    dist_da_voce = dim_voce * 1.5;
    dist_da_voce_principale_voce = dim_voce * 2.0;
    posizione_voci_visibili = 0.0;
    resizeAggiuntivo();
    costruisciCaselle();
}

void MenuAttivo::resize(unsigned dim_x, unsigned dim_y) {
    dim_x_fin = dim_x;
    dim_y_fin = dim_y;
    resize();
}

unsigned MenuAttivo::getVoceSelezionata() {
    return voce_selezionata;
}

void MenuAttivo::setVoceSelezionata(unsigned num_voce){
    voce_selezionata = num_voce;
}

QString MenuAttivo::getStringa() {
    return "";
}