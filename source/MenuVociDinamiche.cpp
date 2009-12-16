/* 
 * File:   MenuCreaLivello.cpp
 * Author: tonegas
 * 
 * Created on 14 dicembre 2009, 22.52
 */

#include "../include/Domino.h"

MenuVociDinamiche::MenuVociDinamiche() {
}

void MenuVociDinamiche::costruisciCaselle() {
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

void MenuVociDinamiche::stampa() {
    font->FaceSize(dim_voce_principale);
    layout->SetAlignment(FTGL::ALIGN_CENTER);
    layout->SetLineLength(dim_x_fin);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(0, dist_da_basso_voce_principale);
    layout->Render(titolo.toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (stati_menu_attivi[i]) {
            glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 1.0f);
            glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
            if (voci_dinamiche[i] != NULL) {
                if(voce_selezionata == i){
                    layout->Render((voci_menu[i]+(*voci_dinamiche[i]) + '_').toStdString().c_str());
                }else{
                    layout->Render((voci_menu[i]+(*voci_dinamiche[i])).toStdString().c_str());
                }
            } else {
                layout->Render(voci_menu[i].toStdString().c_str());
            }
        } else {
            glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 0.3f);
            glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
            layout->Render(voci_menu[i].toStdString().c_str());
        }
    }
}