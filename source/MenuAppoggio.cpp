
#include <FTGL/FTSimpleLayout.h>

#include "../include/Domino.h"

Menu::~Menu() {
    delete font;
}

StatoMenu Menu::getStato() {
    return stato;
}

void Menu::cicloGioco() {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        gestisciInput();
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, dim_x_fin, 0, dim_y_fin);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    stampa();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
//    if (stato_cambio_posticipato != stato) {
//        setStato(stato_cambio_posticipato);
//    }
}

//void Menu::setStatoCambioPosticipato(StatoMenu nuovo_stato) {
//    stato_cambio_posticipato = nuovo_stato;
//}

//bool Menu::gestisciSelezioneMouse() {
//    double pos_x = (double) evento->motion.x;
//    double pos_y = dim_y_fin - (double) evento->motion.y;
//    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
//        if (pos_x < posizioni_caselle_menu_attivo[i].X() + caselle_menu_attivo[i].Upper().X() &&
//                pos_x > posizioni_caselle_menu_attivo[i].X() + caselle_menu_attivo[i].Lower().X() &&
//                pos_y < posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Upper().Y() &&
//                pos_y > posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Lower().Y()) {
//            stato_attivo = i;
//            return true;
//        }
//    }
//    return false;
//}

//bool Menu::gestisciSelezioneMouseMenuLaterale() {
//    double pos_y = dim_y_fin - (double) evento->motion.y;
//    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
//        if (pos_y < posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Upper().Y() &&
//                pos_y > posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Lower().Y()) {
//            stato_attivo = i;
//            return true;
//        }
//    }
//    return false;
//}

//void Menu::inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu) {
//    stato = nuovo_stato;
//    stato_attivo_voci_menu.clear();
//    if (((nuovo_stato / 10) * 10) != 0) {
//        numero_voci_menu_attivo = nuovo_stato % ((nuovo_stato / 10) * 10);
//        stato_attivo_voci_menu.fill(0.0f, numero_voci_menu_attivo);
//    }
//    voci_menu_attivo = nuove_voci_menu;
//    stato_attivo = 0;
//    resize(dim_x_fin, dim_y_fin);
//}
//
//void Menu::inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu, unsigned numero_voci_in_piu) {
//    stato = nuovo_stato;
//    stato_attivo_voci_menu.clear();
//    trasparenza_voci_visibili.clear();
//    if (((nuovo_stato / 10) * 10) != 0) {
//        numero_voci_menu_attivo = nuovo_stato % ((nuovo_stato / 10) * 10) + numero_voci_in_piu;
//        stato_attivo_voci_menu.fill(0.0f, numero_voci_menu_attivo + numero_voci_in_piu);
//        trasparenza_voci_visibili.fill(1.0f, numero_voci_menu_attivo + numero_voci_in_piu);
//    }
//    voci_menu_attivo = nuove_voci_menu;
//    stato_attivo = 0;
//    resize(dim_x_fin, dim_y_fin);
//}

//void Menu::costruisciCaselleMenuCrea() {
//    font->FaceSize(dim_voce);
//    layout.SetAlignment(FTGL::ALIGN_CENTER);
//    layout.SetLineLength(dim_x_fin);
//    posizioni_caselle_menu_attivo.clear();
//    caselle_menu_attivo.clear();
//    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
//        FTPoint aux(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce - dist_da_voce / 2 - dist_da_voce * i);
//        posizioni_caselle_menu_attivo += aux;
//        caselle_menu_attivo += layout.BBox(voci_menu_attivo[i].toStdString().c_str());
//    }
//}
//
//void Menu::stampaMenuInserisciParola() {
//    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//    layout.SetLineLength(dim_x_fin);
//    layout.SetAlignment(FTGL::ALIGN_CENTER);
//    font->FaceSize(dim_voce_principale);
//    glRasterPos2i(0, dist_da_basso_voce_principale + dist_da_voce / 2);
//    layout.Render(voci_menu_attivo[numero_voci_menu_attivo].toStdString().c_str());
//
//    font->FaceSize(dim_voce);
//    glRasterPos2i(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce + dist_da_voce / 2);
//    layout.Render((nuovo_nome + '_').toStdString().c_str());
//    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
//        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 1.0f);
//        glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
//        layout.Render(voci_menu_attivo[i].toStdString().c_str());
//    }
//}

//void Menu::stampaMenuCreaLivello() {
//    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//    layout.SetLineLength(dim_x_fin);
//    layout.SetAlignment(FTGL::ALIGN_CENTER);
//    font->FaceSize(dim_voce_principale);
//    glRasterPos2i(0, dist_da_basso_voce_principale);
//    layout.Render(voci_menu_attivo[numero_voci_menu_attivo].toStdString().c_str());
//
//    font->FaceSize(dim_voce);
//    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
//        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 1.0f);
//        glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
//        switch (i) {
//            case 0:
//                layout.Render((nuovo_nome + '_').toStdString().c_str());
//                break;
//            case 1:
//                layout.Render((voci_menu_attivo[i] + dim_x_nuovo_livello).toStdString().c_str());
//                break;
//            case 2:
//                layout.Render((voci_menu_attivo[i] + dim_y_nuovo_livello).toStdString().c_str());
//                break;
//            default:
//                layout.Render(voci_menu_attivo[i].toStdString().c_str());
//                break;
//        }
//    }
//}

//sarabbe meglio poi usare il genList
//bool primo = true;
//GLuint titolo, nomi;


void Menu::stampaGiocatoreAttuale() {
    font->FaceSize(dim_nome);
    layout.SetAlignment(FTGL::ALIGN_RIGHT);
    layout.SetLineLength(dim_x_fin - dist_da_destra_nome);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(0, dim_y_fin - dist_da_alto_nome);
    layout.Render(gestore_giocatori->nomeGiocatoreAttuale().toStdString().c_str());
}

//void Menu::aggiornaStatoAttivoVociMenu() {
//    menu_attuale.aggiorna();
//    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
//        if (i == stato_attivo) {
//            stato_attivo_voci_menu[i] = 1.0f;
//        } else {
//            stato_attivo_voci_menu[i] = stato_attivo_voci_menu[i] - 0.05 > 0.0 ? stato_attivo_voci_menu[i] - 0.05 : 0.0;
//        }
//    }
//}

//void Menu::aggiornaStatoAttivoVociMenuLaterale() {
//    if (stato_attivo != 0)
//        posizione_voci_visibili = (((double) stato_attivo - 1.0) / (double) numero_voci_menu_attivo)* (numero_voci_menu_attivo + 1 - voci_visibili) * dist_da_voce;
//}

//void Menu::aggiornaStatoAttivoVociMenuLateraleMouse() {
//    if ((int) dim_y_fin - evento->motion.y < (int) dist_da_basso_voce_principale && (int) dim_y_fin - evento->motion.y > (int) dist_da_basso_voce_uscita + dist_da_voce) {
//        posizione_voci_visibili = (double) (dist_da_basso_voce_principale - (dim_y_fin - evento->motion.y))
//                / (double) (dist_da_basso_voce_principale - dist_da_basso_voce_uscita)
//                * (numero_voci_menu_attivo + 2 - voci_visibili) * dist_da_voce;
//    }
//}
