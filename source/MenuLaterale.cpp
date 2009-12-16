/* 
 * File:   MenuLaterale.cpp
 * Author: tonegas
 * 
 * Created on 14 dicembre 2009, 18.43
 */

#include "../include/Domino.h"

MenuLaterale::MenuLaterale() {
}

void MenuLaterale::resizeAggiuntivo() {
    if (dim_x_fin >= 1000 && dim_y_fin >= 1000) {
        dist_da_sinistra = 15;
        dist_da_basso_voce_uscita = 20;
    } else {
        if (dim_x_fin > dim_y_fin) {
            dist_da_sinistra = (float) dim_y_fin / 500.0 * 7;
            dist_da_basso_voce_uscita = (float) dim_y_fin / 500.0 * 10;
        } else {
            dist_da_sinistra = (float) dim_x_fin / 500.0 * 7;
            dist_da_basso_voce_uscita = (float) dim_x_fin / 500.0 * 10;
        }
    }
    dist_da_basso_voce_principale = dim_y_fin - dist_da_sinistra * 4 - 2;
    voci_visibili = (dim_y_fin - (dim_y_fin - dist_da_basso_voce_principale)
            - dist_da_voce_principale_voce) / dist_da_voce + 1;
    voci_visibili = (numero_voci_menu_attivo < voci_visibili) ? numero_voci_menu_attivo : voci_visibili;
}

void MenuLaterale::costruisciCaselle() {
    //qui si può evitare di rifare tutti i conti ogni volta che si sposta il mouse e poi bisognerebbe considerare
    //i nomi da stampare e quelli da non stampare cioè quelli fuori dal video!!!
    layout->SetAlignment(FTGL::ALIGN_LEFT);
    font->FaceSize(dim_voce);
    layout->SetLineLength(dim_x_fin);
    posizioni_caselle_menu_attivo.clear();
    caselle_menu_attivo.clear();
    trasparenza_voci_visibili.clear();
    for (unsigned i = 0; i < numero_voci_menu_attivo - 1; i++) {
        FTPoint aux(dist_da_sinistra, dist_da_basso_voce_principale - dist_da_voce_principale_voce - dist_da_voce * i + posizione_voci_visibili);
        if (aux.Y() > dist_da_basso_voce_principale - dist_da_voce_principale_voce) {
            trasparenza_voci_visibili += 1.0f - (aux.Y() - (dist_da_basso_voce_principale - dist_da_voce_principale_voce))
                    / (dim_y_fin - dist_da_basso_voce_principale + dist_da_voce_principale_voce);
        } else if (aux.Y() < dist_da_basso_voce_uscita + dist_da_voce) {
            trasparenza_voci_visibili += 1.0f - ((dist_da_basso_voce_uscita + dist_da_voce) - aux.Y()) / (dist_da_basso_voce_uscita + dist_da_voce);
        } else {
            trasparenza_voci_visibili += 1.0f;
        }
        posizioni_caselle_menu_attivo += aux;
        caselle_menu_attivo += layout->BBox(voci_menu[i].toStdString().c_str());
    }
    FTPoint aux(dist_da_sinistra, dist_da_basso_voce_uscita);
    posizioni_caselle_menu_attivo += aux;
    caselle_menu_attivo += layout->BBox(voci_menu[numero_voci_menu_attivo - 1].toStdString().c_str());
}

void MenuLaterale::stampa() {
    font->FaceSize(dim_voce_principale);
    layout->SetAlignment(FTGL::ALIGN_LEFT);
    layout->SetLineLength(dim_x_fin);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(dist_da_sinistra, dist_da_basso_voce_principale);
    layout->Render(titolo.toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 0; i < numero_voci_menu_attivo - 1; i++) {
        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], trasparenza_voci_visibili[i]);
        glRasterPos2i(posizioni_caselle_menu_attivo[i].X(), posizioni_caselle_menu_attivo[i].Y());
        layout->Render(voci_menu[i].toStdString().c_str());
    }
    glColor4f(1.0f - stato_attivo_voci_menu[numero_voci_menu_attivo - 1], 1.0f, 1.0f - stato_attivo_voci_menu[numero_voci_menu_attivo - 1], 1.0f);
    glRasterPos2i(posizioni_caselle_menu_attivo[numero_voci_menu_attivo - 1].X(), posizioni_caselle_menu_attivo[numero_voci_menu_attivo - 1].Y());
    layout->Render(voci_menu[numero_voci_menu_attivo - 1].toStdString().c_str());
}

void MenuLaterale::aggiornaMovimento() {
    if (voce_selezionata != numero_voci_menu_attivo - 1) {
        posizione_voci_visibili = ((double) voce_selezionata / (double) numero_voci_menu_attivo)* (numero_voci_menu_attivo + 2 - voci_visibili) * dist_da_voce;
        costruisciCaselle();
    }
}

void MenuLaterale::aggiornaMovimento(unsigned pos_mouse_x, unsigned pos_mouse_y) {
    if ((int) dim_y_fin - (int) pos_mouse_y < (int) dist_da_basso_voce_principale && (int) dim_y_fin - (int) pos_mouse_y > (int) dist_da_basso_voce_uscita + dist_da_voce) {
        posizione_voci_visibili = (double) (dist_da_basso_voce_principale - ((int) dim_y_fin - (int) pos_mouse_y))
                / (double) (dist_da_basso_voce_principale - dist_da_basso_voce_uscita)
                * (numero_voci_menu_attivo + 3 - voci_visibili) * dist_da_voce;
        costruisciCaselle();
    }
}

bool MenuLaterale::gestisciSelezioneMouse(unsigned pos_mouse_x, unsigned pos_mouse_y) {
    double pos_y = dim_y_fin - (double) pos_mouse_y;
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (stati_menu_selezionabili[i]) {
            if (pos_y < posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Upper().Y() &&
                    pos_y > posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Lower().Y()) {
                voce_selezionata = i;
                return true;
            }
        }
    }
    return false;
}

QString MenuLaterale::getStringa() {
    return voci_menu[voce_selezionata];
}