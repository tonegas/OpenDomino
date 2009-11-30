/* 
 * File:   Menu.cpp
 * Author: tonegas
 * 
 * Created on 25 novembre 2009, 1.03
 */


#include "../include/Domino.h"

extern bool alive;

Menu::Menu(GestoreGiocatori *gestore_aux, SDL_Event* evento_aux, unsigned dim_x_fin_aux, unsigned dim_y_fin_aux) {
    gestore = gestore_aux;
    evento = evento_aux;
    dim_x_fin = dim_x_fin_aux;
    dim_y_fin = dim_y_fin_aux;

    visibile = true;

    font = new FTGLPixmapFont("./Caratteri/Abscissa.ttf");
    layout.SetFont(font);

    voci_menu_principale.append("Comincia partita");
    voci_menu_principale.append("Editor livelli");
    voci_menu_principale.append("Opzioni");
    voci_menu_principale.append("Gestione profili");
    voci_menu_principale.append("Istruzioni");
    voci_menu_principale.append("Ringraziamenti");
    voci_menu_principale.append("Esci");
    voci_menu_principale.append("Open Domino");

    voci_menu_gestione_profili.append("Nuovo profilo");
    voci_menu_gestione_profili.append("Cambia profilo");
    voci_menu_gestione_profili.append("Copia profilo attuale");
    voci_menu_gestione_profili.append("Elimina profilo");
    voci_menu_gestione_profili.append("Torna al menu");
    voci_menu_gestione_profili.append("Gestione profili");

    voci_menu_gp_cambia_profilo.append("Torna alla gestione profili");
    voci_menu_gp_cambia_profilo.append("Cambia profilo");

    voci_menu_gp_elimina_profilo.append("Torna alla gestione profili");
    voci_menu_gp_elimina_profilo.append("Elimina profilo");

    voci_menu_gp_nuovo_profilo.append("Crea profilo");
    voci_menu_gp_nuovo_profilo.append("Torna alla gestione profili");
    voci_menu_gp_nuovo_profilo.append("Inserisci nome profilo");

    voci_menu_gp_copia_profilo_attuale.append("Crea copia del profilo");
    voci_menu_gp_copia_profilo_attuale.append("Torna alla gestione profili");
    voci_menu_gp_copia_profilo_attuale.append("Inserisci nome profilo della copia");

    inizializzaVariabiliMenu(PRINCIPALE, voci_menu_principale);
    nome_nuovo_giocatore = "";

    costruisciCaselleMenuCentrale();
}

void Menu::resize(unsigned dim_x, unsigned dim_y) {
    dim_x_fin = dim_x;
    dim_y_fin = dim_y;
    if (dim_x_fin >= 1000 && dim_y_fin >= 1000) {
        dist_da_destra_nome = 15;
        dist_da_sinistra = 15;
        dist_da_alto_nome = 35;
        dim_nome = 30;
        dim_voce_principale = 65;
        dim_voce = 50;
        dist_da_basso_voce_uscita = 20;
    } else {
        if (dim_x_fin > dim_y_fin) {
            dist_da_sinistra = (float) dim_y_fin / 500.0 * 7;
            dist_da_destra_nome = (float) dim_y_fin / 500.0 * 7;
            dist_da_alto_nome = (float) dim_y_fin / 500.0 * 17;
            dim_nome = (float) dim_y_fin / 500.0 * 15;
            dim_voce_principale = (float) dim_y_fin / 500.0 * 32;
            dim_voce = (float) dim_y_fin / 500.0 * 25;
            dist_da_basso_voce_uscita = (float) dim_y_fin / 500.0 * 10;
        } else {
            dist_da_sinistra = (float) dim_x_fin / 500.0 * 7;
            dist_da_destra_nome = (float) dim_x_fin / 500.0 * 7;
            dist_da_alto_nome = (float) dim_x_fin / 500.0 * 17;
            dim_nome = (float) dim_x_fin / 500.0 * 15;
            dim_voce_principale = (float) dim_x_fin / 500.0 * 32;
            dim_voce = (float) dim_x_fin / 500.0 * 25;
            dist_da_basso_voce_uscita = (float) dim_x_fin / 500.0 * 10;
        }
    }
    dist_da_basso_voce_principale = (dim_y_fin / 2 + numero_voci_menu_attivo * dim_voce / 5 * 4);
    dist_da_voce = dim_voce * 1.5;
    dist_da_voce_principale_voce = dim_voce * 2.0;
    posizione_voci_visibili = 0.0;
    switch (stato) {
        case PRINCIPALE:
        case GP_GESTIONE_PROFILI:
            costruisciCaselleMenuCentrale();
            break;
        case GP_EL_ELIMINA_PROFILO:
        case GP_CP_CAMBIA_PROFILO:
            dist_da_basso_voce_principale = dim_y_fin - dist_da_sinistra * 4 - 2;
            voci_visibili = (dim_y_fin - (dim_y_fin - dist_da_basso_voce_principale)
                    - dist_da_voce_principale_voce) / dist_da_voce + 1;
            voci_visibili = (numero_voci_menu_attivo < voci_visibili) ? numero_voci_menu_attivo : voci_visibili;
            costruisciCaselleMenuLaterale();
            break;
        case GP_CPA_COPIA_PROFILO_ATTUALE:
        case GP_NP_NUOVO_PROFILO:
            costruisciCaselleMenuCreaProfilo();
        default:
            break;
    }
}

Menu::~Menu() {
    delete font;
}

void Menu::setStato(Stato_Menu nuovo_stato) {
    stato = nuovo_stato;
}

void Menu::setVisibile(bool aux_visibile) {
    visibile = aux_visibile;
}

Stato_Menu Menu::getStato() {
    return stato;
}

bool Menu::getVisibile() {
    return visibile;
}

void Menu::cicloGioco() {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        gestisciInput();
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, dim_x_fin, 0, dim_y_fin);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    stampa();
}

bool Menu::gestisciSelezioneMouse() {
    double pos_x = (double) evento->motion.x;
    double pos_y = dim_y_fin - (double) evento->motion.y;
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (pos_x < posizioni_caselle_menu_attivo[i].X() + caselle_menu_attivo[i].Upper().X() &&
                pos_x > posizioni_caselle_menu_attivo[i].X() + caselle_menu_attivo[i].Lower().X() &&
                pos_y < posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Upper().Y() &&
                pos_y > posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Lower().Y()) {
            stato_attivo = i;
            return true;
        }
    }
    return false;
}

bool Menu::gestisciSelezioneMouseMenuLaterale() {
    double pos_y = dim_y_fin - (double) evento->motion.y;
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (pos_y < posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Upper().Y() &&
                pos_y > posizioni_caselle_menu_attivo[i].Y() + caselle_menu_attivo[i].Lower().Y()) {
            stato_attivo = i;
            return true;
        }
    }
    return false;
}

void Menu::cambiaVociMenuPrincipale() {
    switch (stato_attivo + 10) {
        case ESCI:
            //alive = false;
            break;
        case GESTIONE_PROFILI:
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
        default:
            break;
    }
}

void Menu::inizializzaVariabiliMenu(Stato_Menu nuovo_stato, QStringList nuove_voci_menu) {
    stato = nuovo_stato;
    stato_attivo_voci_menu.clear();
    if (((nuovo_stato / 10) * 10) != 0) {
        numero_voci_menu_attivo = nuovo_stato % ((nuovo_stato / 10) * 10);
        stato_attivo_voci_menu.fill(0.0f, numero_voci_menu_attivo);
    }
    voci_menu_attivo = nuove_voci_menu;
    stato_attivo = 0;
    resize(dim_x_fin, dim_y_fin);
}

void Menu::inizializzaVariabiliMenu(Stato_Menu nuovo_stato, QStringList nuove_voci_menu, unsigned numero_voci_in_piu) {
    stato = nuovo_stato;
    stato_attivo_voci_menu.clear();
    trasparenza_voci_visibili.clear();
    if (((nuovo_stato / 10) * 10) != 0) {
        numero_voci_menu_attivo = nuovo_stato % ((nuovo_stato / 10) * 10) + numero_voci_in_piu;
        stato_attivo_voci_menu.fill(0.0f, numero_voci_menu_attivo + numero_voci_in_piu);
        trasparenza_voci_visibili.fill(1.0f, numero_voci_menu_attivo + numero_voci_in_piu);
    }
    voci_menu_attivo = nuove_voci_menu;
    stato_attivo = 0;
    resize(dim_x_fin, dim_y_fin);
}

void Menu::cambiaVociMenuGestioneProfili() {
    switch (stato_attivo + GESTIONE_PROFILI * 10) {
        case GP_NUOVO_PROFILO:
            inizializzaVariabiliMenu(GP_NP_NUOVO_PROFILO, voci_menu_gp_nuovo_profilo + (QStringList) nome_nuovo_giocatore);
            nome_nuovo_giocatore.clear();
            costruisciCaselleMenuCreaProfilo();
            break;
        case GP_CAMBIA_PROFILO:
            nomi_giocatori = gestore->nomiGiocatori();
            inizializzaVariabiliMenu(GP_CP_CAMBIA_PROFILO,
                    (QStringList) voci_menu_gp_cambia_profilo[0] + nomi_giocatori + (QStringList) voci_menu_gp_cambia_profilo[1], nomi_giocatori.count());
            costruisciCaselleMenuLaterale();
            break;
        case GP_COPIA_PROFILO_ATTUALE:
            inizializzaVariabiliMenu(GP_CPA_COPIA_PROFILO_ATTUALE, voci_menu_gp_copia_profilo_attuale + (QStringList) nome_nuovo_giocatore);
            nome_nuovo_giocatore.clear();
            costruisciCaselleMenuCreaProfilo();
            break;
        case GP_ELIMINA_PROFILO:
            nomi_giocatori = gestore->nomiGiocatori();
            inizializzaVariabiliMenu(GP_EL_ELIMINA_PROFILO,
                    (QStringList) voci_menu_gp_elimina_profilo[0] + nomi_giocatori + (QStringList) voci_menu_gp_elimina_profilo[1], nomi_giocatori.count());
            costruisciCaselleMenuLaterale();
            break;
        case GP_TORNA_A_MENU_PRINCIPALE:
            inizializzaVariabiliMenu(PRINCIPALE, voci_menu_principale);
            costruisciCaselleMenuCentrale();
            break;
        default:
            break;
    }
}

void Menu::cambiaVociMenuGPCambiaProfilo() {
    switch (stato_attivo + GP_CAMBIA_PROFILO * 10) {
        case GP_CP_TORNA_A_MENU_GESTIONE_PROFILI:
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
        default:
            gestore->cambiaGiocatore(nomi_giocatori[stato_attivo - 1]);
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
    }
}

void Menu::cambiaVociMenuGPEliminaProfilo() {
    //aggiungere una schermata dove si dice sicuro di voler eliminare il giocatore comic si no
    switch (stato_attivo + GP_ELIMINA_PROFILO * 10) {
        case GP_EL_TORNA_A_MENU_GESTIONE_PROFILI:
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
        default:
            gestore->eliminaGiocatore(nomi_giocatori[stato_attivo - 1]);
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
    }
}

void Menu::cambiaVociMenuGPNuovoProfilo() {
    switch (stato_attivo + GP_NUOVO_PROFILO * 10) {
        case GP_NP_TORNA_A_MENU_GESTIONE_PROFILI:
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
        case GP_NP_CREA_PROFILO:
            if (gestore->nuovoGiocatore(nome_nuovo_giocatore)) {
                inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
                costruisciCaselleMenuCentrale();
            }
            break;
    }
}

void Menu::cambiaVociMenuGPCopiaProfiloAttuale() {
    switch (stato_attivo + GP_COPIA_PROFILO_ATTUALE * 10) {
        case GP_CPA_TORNA_A_MENU_GESTIONE_PROFILI:
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
        case GP_CPA_CREA_COPIA_PROFILO:
            if (gestore->copiaGiocatoreAttuale(nome_nuovo_giocatore)) {
                inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
                costruisciCaselleMenuCentrale();
            }
            break;
    }
}

void Menu::cambiaVociMenu() {
    switch (stato) {
        case PRINCIPALE:
            cambiaVociMenuPrincipale();
            break;
        case GP_GESTIONE_PROFILI:
            cambiaVociMenuGestioneProfili();
            break;
        case GP_CP_CAMBIA_PROFILO:
            cambiaVociMenuGPCambiaProfilo();
            break;
        case GP_EL_ELIMINA_PROFILO:
            cambiaVociMenuGPEliminaProfilo();
            break;
        case GP_NP_NUOVO_PROFILO:
            cambiaVociMenuGPNuovoProfilo();
            break;
        case GP_CPA_COPIA_PROFILO_ATTUALE:
            cambiaVociMenuGPCopiaProfiloAttuale();
            break;
        default:
            break;
    }
}

void Menu::gestisciInput() {
    switch (evento->type) {
        case SDL_KEYDOWN:
            if (evento->key.state == SDL_PRESSED) {
                switch (evento->key.keysym.sym) {
                    case SDLK_UP:
                        stato_attivo = (stato_attivo - 1) >= numero_voci_menu_attivo ? (numero_voci_menu_attivo - 1) : (stato_attivo - 1);
                        if ((stato == GP_EL_ELIMINA_PROFILO || stato == GP_CP_CAMBIA_PROFILO) && numero_voci_menu_attivo > voci_visibili) {
                            aggiornaStatoAttivoVociMenuLaterale();
                            costruisciCaselleMenuLaterale();
                        }
                        break;
                    case SDLK_DOWN:
                        stato_attivo = ((stato_attivo + 1) % numero_voci_menu_attivo);
                        if ((stato == GP_EL_ELIMINA_PROFILO || stato == GP_CP_CAMBIA_PROFILO) && numero_voci_menu_attivo > voci_visibili) {
                            aggiornaStatoAttivoVociMenuLaterale();
                            costruisciCaselleMenuLaterale();
                        }
                        break;
                    case SDLK_RETURN:
                        cambiaVociMenu();
                        break;
                    case SDLK_ESCAPE:
                        if (stato != PRINCIPALE) {
                            stato_attivo = (stato % (stato / 10 * 10)) - 1;
                            cambiaVociMenu();
                        } else {
                            visibile = false;
                        }
                        break;
                    default:
                        if (stato == GP_NP_NUOVO_PROFILO || stato == GP_CPA_COPIA_PROFILO_ATTUALE) {
                            if (evento->key.keysym.sym <= 122 && evento->key.keysym.sym >= 97 && nome_nuovo_giocatore.count() <= 30) {
                                if (evento->key.keysym.mod & KMOD_SHIFT) {
                                    nome_nuovo_giocatore += evento->key.keysym.sym - 32;
                                } else {
                                    nome_nuovo_giocatore += evento->key.keysym.sym;
                                }
                            }
                            if (evento->key.keysym.sym == SDLK_BACKSPACE) {
                                nome_nuovo_giocatore.resize(nome_nuovo_giocatore.count() - 1);
                            }
                        }
                        break;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if ((stato == GP_EL_ELIMINA_PROFILO || stato == GP_CP_CAMBIA_PROFILO) && numero_voci_menu_attivo > voci_visibili) {
                aggiornaStatoAttivoVociMenuLateraleMouse();
                costruisciCaselleMenuLaterale();
                gestisciSelezioneMouseMenuLaterale();
            } else {
                gestisciSelezioneMouse();
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (evento->button.button == SDL_BUTTON_LEFT)
                if (gestisciSelezioneMouse()) {
                    cambiaVociMenu();
                }
            break;
        default:
            break;
    }
}

void Menu::stampa() {
    switch (stato) {
        case PRINCIPALE:
        case GP_GESTIONE_PROFILI:
            stampaMenuCentrale();
            break;
        case GP_EL_ELIMINA_PROFILO:
        case GP_CP_CAMBIA_PROFILO:
            stampaMenuLaterale();
            break;
        case GP_CPA_COPIA_PROFILO_ATTUALE:
        case GP_NP_NUOVO_PROFILO:
            stampaMenuCreaProfilo();
        default:
            break;
    }
    stampaGiocatoreAttuale();
    aggiornaStatoAttivoVociMenu();
}

void Menu::costruisciCaselleMenuCreaProfilo() {
    font->FaceSize(dim_voce);
    layout.SetAlignment(FTGL::ALIGN_CENTER);
    layout.SetLineLength(dim_x_fin);
    posizioni_caselle_menu_attivo.clear();
    caselle_menu_attivo.clear();
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        FTPoint aux(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce - dist_da_voce / 2 - dist_da_voce * i);
        posizioni_caselle_menu_attivo += aux;
        caselle_menu_attivo += layout.BBox(voci_menu_attivo[i].toStdString().c_str());
    }
}

void Menu::stampaMenuCreaProfilo() {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    layout.SetLineLength(dim_x_fin);
    layout.SetAlignment(FTGL::ALIGN_CENTER);
    font->FaceSize(dim_voce_principale);
    glRasterPos2i(0, dist_da_basso_voce_principale + dist_da_voce / 2);
    layout.Render(voci_menu_attivo[numero_voci_menu_attivo].toStdString().c_str());

    font->FaceSize(dim_voce);
    glRasterPos2i(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce + dist_da_voce / 2);
    layout.Render((nome_nuovo_giocatore + '_').toStdString().c_str());
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 1.0f);
        glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
        layout.Render(voci_menu_attivo[i].toStdString().c_str());
    }
}

void Menu::costruisciCaselleMenuCentrale() {
    layout.SetAlignment(FTGL::ALIGN_CENTER);
    font->FaceSize(dim_voce);
    layout.SetLineLength(dim_x_fin);
    posizioni_caselle_menu_attivo.clear();
    caselle_menu_attivo.clear();
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        FTPoint aux(0, dist_da_basso_voce_principale - dist_da_voce_principale_voce - dist_da_voce * i);
        posizioni_caselle_menu_attivo += aux;
        caselle_menu_attivo += layout.BBox(voci_menu_attivo[i].toStdString().c_str());
    }
}

void Menu::stampaMenuCentrale() {
    font->FaceSize(dim_voce_principale);
    layout.SetAlignment(FTGL::ALIGN_CENTER);
    layout.SetLineLength(dim_x_fin);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(0, dist_da_basso_voce_principale);
    layout.Render(voci_menu_attivo[numero_voci_menu_attivo].toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], 1.0f);
        glRasterPos2i(0, posizioni_caselle_menu_attivo[i].Y());
        layout.Render(voci_menu_attivo[i].toStdString().c_str());
        glPushMatrix();
        //        glTranslatef(posizioni_caselle_menu_attivo[i].X(), posizioni_caselle_menu_attivo[i].Y(), 0);
        //        glBegin(GL_LINE_LOOP);
        //        {
        //            glVertex2d(caselle_menu_attivo[i].Lower().X(), caselle_menu_attivo[i].Lower().Y());
        //            glVertex2d(caselle_menu_attivo[i].Lower().X(), caselle_menu_attivo[i].Upper().Y());
        //            glVertex2d(caselle_menu_attivo[i].Upper().X(), caselle_menu_attivo[i].Upper().Y());
        //            glVertex2d(caselle_menu_attivo[i].Upper().X(), caselle_menu_attivo[i].Lower().Y());
        //        }
        //        glEnd();
        //        glPopMatrix();
    }
}

void Menu::costruisciCaselleMenuLaterale() {
    layout.SetAlignment(FTGL::ALIGN_LEFT);
    font->FaceSize(dim_voce);
    layout.SetLineLength(dim_x_fin);
    posizioni_caselle_menu_attivo.clear();
    caselle_menu_attivo.clear();
    FTPoint aux(dist_da_sinistra, dist_da_basso_voce_uscita);
    posizioni_caselle_menu_attivo += aux;
    caselle_menu_attivo += layout.BBox(voci_menu_attivo[0].toStdString().c_str());
    for (unsigned i = 1; i < numero_voci_menu_attivo; i++) {
        FTPoint aux(dist_da_sinistra, dist_da_basso_voce_principale - dist_da_voce_principale_voce + dist_da_voce - dist_da_voce * i + posizione_voci_visibili);
        if(aux.Y() > dist_da_basso_voce_principale - dist_da_voce_principale_voce){
            trasparenza_voci_visibili[i] = 1.0f-(aux.Y() - (dist_da_basso_voce_principale - dist_da_voce_principale_voce))
                    /(dim_y_fin - dist_da_basso_voce_principale + dist_da_voce_principale_voce);
        }else if(aux.Y() < dist_da_basso_voce_uscita + dist_da_voce){
            trasparenza_voci_visibili[i] = 1.0f-((dist_da_basso_voce_uscita + dist_da_voce) - aux.Y())/(dist_da_basso_voce_uscita + dist_da_voce);
        }else{
            trasparenza_voci_visibili[i] = 1.0f;
        }
        posizioni_caselle_menu_attivo += aux;
        caselle_menu_attivo += layout.BBox(voci_menu_attivo[i].toStdString().c_str());
    }
}

void Menu::stampaMenuLaterale() {
    font->FaceSize(dim_voce_principale);
    layout.SetAlignment(FTGL::ALIGN_LEFT);
    layout.SetLineLength(dim_x_fin);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(dist_da_sinistra, dist_da_basso_voce_principale);
    layout.Render(voci_menu_attivo[numero_voci_menu_attivo].toStdString().c_str());

    font->FaceSize(dim_voce);
    for (unsigned i = 1; i < numero_voci_menu_attivo; i++) {
        glColor4f(1.0f - stato_attivo_voci_menu[i], 1.0f, 1.0f - stato_attivo_voci_menu[i], trasparenza_voci_visibili[i]);
        glRasterPos2i(posizioni_caselle_menu_attivo[i].X(), posizioni_caselle_menu_attivo[i].Y());
        layout.Render(voci_menu_attivo[i].toStdString().c_str());
    }
    glColor4f(1.0f - stato_attivo_voci_menu[0], 1.0f, 1.0f - stato_attivo_voci_menu[0], 1.0f);
    glRasterPos2i(posizioni_caselle_menu_attivo[0].X(), posizioni_caselle_menu_attivo[0].Y());
    layout.Render(voci_menu_attivo[0].toStdString().c_str());
}

void Menu::stampaGiocatoreAttuale() {
    font->FaceSize(dim_nome);
    layout.SetAlignment(FTGL::ALIGN_RIGHT);
    layout.SetLineLength(dim_x_fin - dist_da_destra_nome);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(0, dim_y_fin - dist_da_alto_nome);
    layout.Render(gestore->nomeGiocatoreAttuale().toStdString().c_str());
}

void Menu::aggiornaStatoAttivoVociMenu() {
    for (unsigned i = 0; i < numero_voci_menu_attivo; i++) {
        if (i == stato_attivo) {
            stato_attivo_voci_menu[i] = 1.0f;
        } else {
            stato_attivo_voci_menu[i] = stato_attivo_voci_menu[i] - 0.05 > 0.0 ? stato_attivo_voci_menu[i] - 0.05 : 0.0;
        }
    }
}

void Menu::aggiornaStatoAttivoVociMenuLaterale() {
    if (stato_attivo != 0)
        posizione_voci_visibili = (((double) stato_attivo - 1.0) / (double) numero_voci_menu_attivo)* (numero_voci_menu_attivo + 1 - voci_visibili) * dist_da_voce;
}

void Menu::aggiornaStatoAttivoVociMenuLateraleMouse() {
    if ((int)dim_y_fin - evento->motion.y < (int)dist_da_basso_voce_principale && (int)dim_y_fin - evento->motion.y > (int)dist_da_basso_voce_uscita + dist_da_voce) {
        posizione_voci_visibili = (double) (dist_da_basso_voce_principale - (dim_y_fin - evento->motion.y))
                / (double) (dist_da_basso_voce_principale - dist_da_basso_voce_uscita)
                * (numero_voci_menu_attivo + 1 - voci_visibili) * dist_da_voce;
    }
}
