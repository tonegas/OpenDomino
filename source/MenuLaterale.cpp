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
    //    voci_visibili = (dim_y_fin - (dim_y_fin - dist_da_basso_voce_principale)
    //            - dist_da_voce_principale_voce) / dist_da_voce + 1;
    voci_visibili = (dim_y_fin - (dim_y_fin - dist_da_basso_voce_principale)
            - dist_da_voce_principale_voce - dist_da_basso_voce_uscita - dist_da_voce) / dist_da_voce + 1;
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
    trasparenza_voci_visibili += 1.0f;
    posizioni_caselle_menu_attivo += aux;
    caselle_menu_attivo += layout->BBox(voci_menu[numero_voci_menu_attivo - 1].toStdString().c_str());
    sinistra = 0;
    destra = dim_x_fin;
}

void MenuLaterale::stampa() {
    font->FaceSize(dim_voce_principale);
    layout->SetAlignment(FTGL::ALIGN_LEFT);
    layout->SetLineLength(dim_x_fin);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(dist_da_sinistra, dist_da_basso_voce_principale);
    layout->Render(titolo.toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        glColor4f(0.8, 0.8, 0.8, stato_attivo_voci_menu[i]*0.6);
        glBegin(GL_QUADS);
        {
            glVertex2d((double) sinistra + (double) dist_da_voce / 8.0, (double) posizioni_caselle_menu_attivo[i].Y() - (double) dist_da_voce / 5.2);
            glVertex2d((double) sinistra + (double) dist_da_voce / 8.0, (double) posizioni_caselle_menu_attivo[i].Y() + (double) dist_da_voce / 1.8);
            glVertex2d((double) destra - (double) dist_da_voce / 8.0, (double) posizioni_caselle_menu_attivo[i].Y() + (double) dist_da_voce / 1.8);
            glVertex2d((double) destra - (double) dist_da_voce / 8.0, (double) posizioni_caselle_menu_attivo[i].Y() - (double) dist_da_voce / 5.2);
        }
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, trasparenza_voci_visibili[i]);
        glRasterPos2i(posizioni_caselle_menu_attivo[i].X(), posizioni_caselle_menu_attivo[i].Y());
        layout->Render(voci_menu[i].toStdString().c_str());
    }
}

void MenuLaterale::aggiornaMovimento() {
    if (voce_selezionata != numero_voci_menu_attivo - 1) {
        posizione_voci_visibili = ((double) voce_selezionata / (double) numero_voci_menu_attivo)* (numero_voci_menu_attivo - voci_visibili) * dist_da_voce;
        costruisciCaselle();
    }
}

void MenuLaterale::aggiornaMovimento(unsigned pos_mouse_x, unsigned pos_mouse_y) {
    PARAMETRO_NON_USATO(pos_mouse_x);
    if ((int) dim_y_fin - (int) pos_mouse_y < ((int) dist_da_basso_voce_principale - dist_da_voce_principale_voce)
            && (int) dim_y_fin - (int) pos_mouse_y > (int) dist_da_basso_voce_uscita + dist_da_voce) {
        posizione_voci_visibili = (double) ((int)pos_mouse_y - (int)dist_da_voce_principale_voce - ((int) dim_y_fin - (int)dist_da_basso_voce_principale)) /
                (double) (dim_y_fin - dist_da_basso_voce_uscita - dist_da_voce - dist_da_voce_principale_voce - ((int) dim_y_fin - (int)dist_da_basso_voce_principale))
                * (numero_voci_menu_attivo - 1 - voci_visibili) * dist_da_voce;
        costruisciCaselle();
    }
}

bool MenuLaterale::gestisciSelezioneMouse(unsigned pos_mouse_x, unsigned pos_mouse_y) {
    PARAMETRO_NON_USATO(pos_mouse_x);
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