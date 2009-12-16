/* 
 * File:   MenuCreaLivello.cpp
 * Author: tonegas
 * 
 * Created on 14 dicembre 2009, 22.52
 */

#include "../include/Domino.h"

MenuCreaLivello::MenuCreaLivello() {
}

void MenuCreaLivello::costruisciCaselle() {
    layout->SetAlignment(FTGL::ALIGN_CENTER);
    font->FaceSize(dim_voce);
    layout->SetLineLength(dim_x_fin);
    posizioni_caselle_menu_attivo.clear();
    caselle_menu_attivo.clear();
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        FTPoint aux(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce - dist_da_voce * i);
        posizioni_caselle_menu_attivo += aux;
        caselle_menu_attivo += layout->BBox(voci_menu[i].toStdString().c_str());
    }
}

void MenuCreaLivello::stampa() {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    layout->SetLineLength(dim_x_fin);
    layout->SetAlignment(FTGL::ALIGN_CENTER);
    font->FaceSize(dim_voce_principale);
    glRasterPos2i(0, dist_da_basso_voce_principale);
    layout->Render(voci_menu[numero_voci_menu_attivo].toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 1.0f);
        glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
        switch (i) {
            case 0:
                layout->Render((nuovo_nome + '_').toStdString().c_str());
                break;
            case 1:
                layout->Render((voci_menu[i] + dim_x_nuovo_livello).toStdString().c_str());
                break;
            case 2:
                layout->Render((voci_menu[i] + dim_y_nuovo_livello).toStdString().c_str());
                break;
            default:
                layout->Render(voci_menu[i].toStdString().c_str());
                break;
        }
    }
}