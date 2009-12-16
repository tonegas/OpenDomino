/* 
 * File:   MenuCentrale.cpp
 * Author: tonegas
 * 
 * Created on 14 dicembre 2009, 18.35
 */

#include <FTGL/FTBBox.h>

#include "../include/Domino.h"

MenuCentrale::MenuCentrale() {
}

void MenuCentrale::costruisciCaselle() {
    layout->SetAlignment(FTGL::ALIGN_CENTER);
    layout->SetLineLength(dim_x_fin);

    font->FaceSize(dim_voce_principale);
    glRasterPos2i(0, dist_da_basso_voce_principale);
    FTBBox aux = layout->BBox(titolo.toStdString().c_str());
    sinistra = aux.Lower().X();
    destra = aux.Upper().X();
    sopra = aux.Upper().Y() + dist_da_basso_voce_principale + dist_da_voce / 2;

    font->FaceSize(dim_voce);
    posizioni_caselle_menu_attivo.clear();
    caselle_menu_attivo.clear();
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        FTPoint aux(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce - dist_da_voce * i);
        posizioni_caselle_menu_attivo += aux;
        caselle_menu_attivo += layout->BBox(voci_menu[i].toStdString().c_str());
        destra = (destra < caselle_menu_attivo[i].Upper().X()) ? caselle_menu_attivo[i].Upper().X() : destra;
        sinistra = (sinistra > caselle_menu_attivo[i].Lower().X()) ? caselle_menu_attivo[i].Lower().X() : sinistra;
    }
    sotto = caselle_menu_attivo[numero_voci_menu_attivo - 1].Lower().Y() + posizioni_caselle_menu_attivo[numero_voci_menu_attivo - 1].Y() - dist_da_voce / 2;
    destra += dist_da_voce / 2;
    sinistra -= dist_da_voce / 2;
}

void MenuCentrale::stampa() {
//    glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
//    glBegin(GL_QUADS);
//    {
//        glVertex2i(sinistra, sopra);
//        glVertex2i(sinistra, sotto);
//        glVertex2i(destra, sotto);
//        glVertex2i(destra, sopra);
//    }
//    glEnd();
    font->FaceSize(dim_voce_principale);
    layout->SetAlignment(FTGL::ALIGN_CENTER);
    layout->SetLineLength(dim_x_fin);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(0, dist_da_basso_voce_principale);
    layout->Render(titolo.toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        glColor4f(0.8, 0.8, 0.8, stato_attivo_voci_menu[i]*0.6);
        glBegin(GL_QUADS);
        {
            glVertex2d((double)sinistra + (double)dist_da_voce / 4.0, (double)posizioni_caselle_menu_attivo[i].Y() - (double)dist_da_voce / 5.2);
            glVertex2d((double)sinistra + (double)dist_da_voce / 4.0, (double)posizioni_caselle_menu_attivo[i].Y() + (double)dist_da_voce / 1.8);
            glVertex2d((double)destra - (double)dist_da_voce / 4.0, (double)posizioni_caselle_menu_attivo[i].Y() + (double)dist_da_voce / 1.8);
            glVertex2d((double)destra - (double)dist_da_voce / 4.0, (double)posizioni_caselle_menu_attivo[i].Y() - (double)dist_da_voce / 5.2);
        }
        glEnd();
        if (stati_menu_attivi[i]) {
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
        }
        glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
        layout->Render(voci_menu[i].toStdString().c_str());
    }
}