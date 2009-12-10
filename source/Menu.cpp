/* 
 * File:   Menu.cpp
 * Author: tonegas
 * 
 * Created on 25 novembre 2009, 1.03
 */


#include "../include/Domino.h"

Menu::Menu(unsigned dim_x_fin_aux, unsigned dim_y_fin_aux) {
    gestore_giocatori = gioco->getGestoreGiocatori();
    dim_x_fin = dim_x_fin_aux;
    dim_y_fin = dim_y_fin_aux;

    font = new FTGLPixmapFont("./Caratteri/Abscissa.ttf");
    layout.SetFont(font);

    //::::::::::::::::::::::::::::::::::
    voci_menu_principale.append("Gioca");
    voci_menu_principale.append("Editor livelli");
    voci_menu_principale.append("Opzioni");
    voci_menu_principale.append("Gestione profili");
    voci_menu_principale.append("Istruzioni");
    voci_menu_principale.append("Ringraziamenti");
    voci_menu_principale.append("Esci");
    voci_menu_principale.append("Open Domino");

    voci_menu_gioca.append("Continua ultimo livello");
    voci_menu_gioca.append("Cambia livello");
    voci_menu_gioca.append("Torna al menu");
    voci_menu_gioca.append("Gioca");

    voci_menu_g_scegli_livello.append("Torna al menu");
    voci_menu_g_scegli_livello.append("Scegli livello");

    voci_menu_gestione_livelli.append("Nuovo livello");
    voci_menu_gestione_livelli.append("Scegli livello");
    voci_menu_gestione_livelli.append("Elimina livello");
    voci_menu_gestione_livelli.append("Torna al menu");
    voci_menu_gestione_livelli.append("Editor livelli");

    voci_menu_gel_nuovo_livello.append("Crea livello");
    voci_menu_gel_nuovo_livello.append("Torna indietro");
    voci_menu_gel_nuovo_livello.append("Nuovo livello");

    voci_menu_gel_scegli_livello.append("Torna indietro");
    voci_menu_gel_scegli_livello.append("Scegli livello");

    voci_menu_gel_elimina_livello.append("Torna indietro");
    voci_menu_gel_elimina_livello.append("Elimina livello");

    //    voci_menu_continua_livello.append("Continua");
    //    voci_menu_continua_livello.append("Salva livello");
    //    voci_menu_continua_livello.append("Torna al menu principale");
    //    voci_menu_continua_livello.append("Open Domino");

    voci_menu_gestione_profili.append("Nuovo profilo");
    voci_menu_gestione_profili.append("Cambia profilo");
    voci_menu_gestione_profili.append("Copia profilo attuale");
    voci_menu_gestione_profili.append("Elimina profilo");
    voci_menu_gestione_profili.append("Torna al menu");
    voci_menu_gestione_profili.append("Gestione profili");

    voci_menu_gp_cambia_profilo.append("Torna indietro");
    voci_menu_gp_cambia_profilo.append("Cambia profilo");

    voci_menu_gp_elimina_profilo.append("Torna indietro");
    voci_menu_gp_elimina_profilo.append("Elimina profilo");

    voci_menu_gp_nuovo_profilo.append("Crea profilo");
    voci_menu_gp_nuovo_profilo.append("Torna indietro");
    voci_menu_gp_nuovo_profilo.append("Inserisci nome profilo");

    voci_menu_gp_copia_profilo_attuale.append("Crea copia del profilo");
    voci_menu_gp_copia_profilo_attuale.append("Torna indietro");
    voci_menu_gp_copia_profilo_attuale.append("Inserisci nome profilo della copia");
    //::::::::::::::::::::::::::::::::::

    //::::::::::::::::::::::::::::::::::
    voci_menu_el_editor_livello.append("Prova livello");
    voci_menu_el_editor_livello.append("Salva livello");
    voci_menu_el_editor_livello.append("Salva con nome livello");
    voci_menu_el_editor_livello.append("Cambia livello");
    voci_menu_el_editor_livello.append("Torna al menu principale");
    voci_menu_el_editor_livello.append("Open Domino");

    voci_menu_el_salva_con_nome.append("Salva livello");
    voci_menu_el_salva_con_nome.append("Torna indietro");
    voci_menu_el_salva_con_nome.append("Scegli nome livello");

    voci_menu_el_cambia_livello.append("Torna indietro");
    voci_menu_el_cambia_livello.append("Scegli Livello");
    //::::::::::::::::::::::::::::::::::

    //::::::::::::::::::::::::::::::::::
    voci_menu_gl_gioca_livello.append("Salva livello");
    voci_menu_gl_gioca_livello.append("Cambia Livello");
    voci_menu_gl_gioca_livello.append("Torna al menu principale");
    voci_menu_gl_gioca_livello.append("Open Domino");

    voci_menu_gl_cambia_livello.append("Torna indietro");
    voci_menu_gl_cambia_livello.append("Scegli Livello");
    //::::::::::::::::::::::::::::::::::

    //::::::::::::::::::::::::::::::::::
    voci_menu_elp_editor_livello_prova.append("Torna all'editor");
    voci_menu_elp_editor_livello_prova.append("Torna al menu principale");
    voci_menu_elp_editor_livello_prova.append("Open Domino");
    //::::::::::::::::::::::::::::::::::

    nome_nuovo_giocatore = "";
    setStato(PRINCIPALE);
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
            costruisciCaselleMenuCrea();
        default:
            costruisciCaselleMenuCentrale();
            break;
    }
}

void Menu::setStato(StatoMenu nuovo_stato) {
    switch (nuovo_stato) {
        case PRINCIPALE:
            inizializzaVariabiliMenu(PRINCIPALE, voci_menu_principale);
            costruisciCaselleMenuCentrale();
            break;
            //--------------------------
        case G_GIOCA:
            inizializzaVariabiliMenu(G_GIOCA, voci_menu_gioca);
            costruisciCaselleMenuCentrale();
            break;
        case G_SL_SCEGLI_LIVELLO:
            inizializzaVariabiliMenu(G_SL_SCEGLI_LIVELLO,
                    (QStringList) voci_menu_g_scegli_livello[0] + lista_livelli + (QStringList) voci_menu_g_scegli_livello[1], lista_livelli.count());
            costruisciCaselleMenuLaterale();
            break;
            //--------------------------
        case GEL_GESTIONE_LIVELLI:
            inizializzaVariabiliMenu(GEL_GESTIONE_LIVELLI, voci_menu_gestione_livelli);
            costruisciCaselleMenuCentrale();
            break;
        case GEL_NL_NUOVO_LIVELLO:
            inizializzaVariabiliMenu(GEL_NL_NUOVO_LIVELLO, voci_menu_gel_nuovo_livello + (QStringList) nome_nuovo_livello);
            costruisciCaselleMenuCrea();
            break;
        case GEL_SL_SCEGLI_LIVELLO:
            inizializzaVariabiliMenu(GEL_SL_SCEGLI_LIVELLO,
                    (QStringList) voci_menu_gel_scegli_livello[0] + lista_livelli + (QStringList) voci_menu_gel_scegli_livello[1], lista_livelli.count());
            costruisciCaselleMenuLaterale();
            break;
        case GEL_EL_ELIMINA_LIVELLO:
            inizializzaVariabiliMenu(GEL_EL_ELIMINA_LIVELLO,
                    (QStringList) voci_menu_gel_elimina_livello[0] + lista_livelli + (QStringList) voci_menu_gel_elimina_livello[1], lista_livelli.count());
            costruisciCaselleMenuLaterale();
            break;
            //--------------------------
        case GP_GESTIONE_PROFILI:
            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
            costruisciCaselleMenuCentrale();
            break;
        case GP_NP_NUOVO_PROFILO:
            inizializzaVariabiliMenu(GP_NP_NUOVO_PROFILO, voci_menu_gp_nuovo_profilo + (QStringList) nome_nuovo_giocatore);
            costruisciCaselleMenuCrea();
            break;
        case GP_CP_CAMBIA_PROFILO:
            inizializzaVariabiliMenu(GP_CP_CAMBIA_PROFILO,
                    (QStringList) voci_menu_gp_cambia_profilo[0] + nomi_giocatori + (QStringList) voci_menu_gp_cambia_profilo[1], nomi_giocatori.count());
            costruisciCaselleMenuLaterale();
            break;
        case GP_EL_ELIMINA_PROFILO:
            inizializzaVariabiliMenu(GP_EL_ELIMINA_PROFILO,
                    (QStringList) voci_menu_gp_elimina_profilo[0] + nomi_giocatori + (QStringList) voci_menu_gp_elimina_profilo[1], nomi_giocatori.count());
            costruisciCaselleMenuLaterale();
            break;
        case GP_CPA_COPIA_PROFILO_ATTUALE:
            inizializzaVariabiliMenu(GP_CPA_COPIA_PROFILO_ATTUALE, voci_menu_gp_copia_profilo_attuale + (QStringList) nome_nuovo_giocatore);
            costruisciCaselleMenuCrea();
            break;
            //--------------------------
            //:::::::::::::::::::::::::::::::::::
            
        default:
            cout << "ERRORE DI INDIRIZZAMENTO MENU" << flush;
            break;
    }
}

void Menu::gestisciInput() {
    if (evento->type == SDL_QUIT) {
        gioco->gameExit();
    }
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
                            if (stato == CL_CONTINUA_LIVELLO) {
                                gioco->setStato(GIOCATORE);
                            } else {
                                stato_attivo = (stato % (stato / 10 * 10)) - 1;
                                cambiaVociMenu();
                            }
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
        case SDL_VIDEORESIZE:
            gioco->resize(evento->resize.w, evento->resize.h);
            break;
        default:
            break;
    }
}

void Menu::stampa() {
    switch (stato) {
        case GP_EL_ELIMINA_PROFILO:
        case GP_CP_CAMBIA_PROFILO:
            stampaMenuLaterale();
            break;
        case GP_CPA_COPIA_PROFILO_ATTUALE:
        case GP_NP_NUOVO_PROFILO:
            stampaMenuCreaProfilo();
            break;
        default:
            stampaMenuCentrale();
            break;
    }
    stampaGiocatoreAttuale();
    aggiornaStatoAttivoVociMenu();
}


void Menu::cambiaVociMenu() {
    switch (stato) {
        case PRINCIPALE:
            cambiaVociMenuPrincipale();
            break;
        case CL_CONTINUA_LIVELLO:
            cambiaVociMenuContinuaLivello();
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

void Menu::cambiaVociMenuPrincipale() {
    switch (stato_attivo + 10) {
        case ESCI:
            gioco->gameExit();
            break;
        case GIOCA:
            setStato(G_GIOCA);
            break;
        case GESTIONE_LIVELLI:
            setStato(GEL_GESTIONE_LIVELLI);
            break;
        case GESTIONE_PROFILI:
            setStato(GP_GESTIONE_PROFILI);
            break;
        default:
            break;
    }
}



void Menu::cambiaVociMenuGestioneProfili() {
    switch (stato_attivo + GESTIONE_PROFILI * 10) {
        case GP_NUOVO_PROFILO:
            setStato(GP_NP_NUOVO_PROFILO);
            nome_nuovo_giocatore.clear();
            break;
        case GP_CAMBIA_PROFILO:
            nomi_giocatori = gestore_giocatori->nomiGiocatori();
            setStato(GP_CP_CAMBIA_PROFILO);
            break;
        case GP_COPIA_PROFILO_ATTUALE:
            setStato(GP_CPA_COPIA_PROFILO_ATTUALE);
            nome_nuovo_giocatore.clear();
            break;
        case GP_ELIMINA_PROFILO:
            nomi_giocatori = gestore_giocatori->nomiGiocatori();
            setStato(GP_EL_ELIMINA_PROFILO);
            break;
        case GP_TORNA_A_MENU_PRINCIPALE:
            setStato(PRINCIPALE);
            break;
        default:
            break;
    }
}

void Menu::cambiaVociMenuGPCambiaProfilo() {
    switch (stato_attivo + GP_CAMBIA_PROFILO * 10) {
        case GP_CP_TORNA_A_MENU_GESTIONE_PROFILI:
            setStato(GP_GESTIONE_PROFILI);
            break;
        default:
            gestore_giocatori->cambiaGiocatore(nomi_giocatori[stato_attivo - 1]);
            setStato(PRINCIPALE);
            break;
    }
}

void Menu::cambiaVociMenuGPEliminaProfilo() {
    //aggiungere una schermata dove si dice sicuro di voler eliminare il giocatore comic si no
    switch (stato_attivo + GP_ELIMINA_PROFILO * 10) {
        case GP_EL_TORNA_A_MENU_GESTIONE_PROFILI:
            setStato(GP_GESTIONE_PROFILI);
            break;
        default:
            gestore_giocatori->eliminaGiocatore(nomi_giocatori[stato_attivo - 1]);
            setStato(GP_GESTIONE_PROFILI);
            break;
    }
}

void Menu::cambiaVociMenuGPNuovoProfilo() {
    switch (stato_attivo + GP_NUOVO_PROFILO * 10) {
        case GP_NP_TORNA_A_MENU_GESTIONE_PROFILI:
            setStato(GP_GESTIONE_PROFILI);
            break;
        case GP_NP_CREA_PROFILO:
            if (gestore_giocatori->nuovoGiocatore(nome_nuovo_giocatore)) {
                setStato(PRINCIPALE);
            }
            break;
    }
}

void Menu::cambiaVociMenuGPCopiaProfiloAttuale() {
    switch (stato_attivo + GP_COPIA_PROFILO_ATTUALE * 10) {
        case GP_CPA_TORNA_A_MENU_GESTIONE_PROFILI:
            setStato(GP_GESTIONE_PROFILI);
            break;
        case GP_CPA_CREA_COPIA_PROFILO:
            if (gestore_giocatori->copiaGiocatoreAttuale(nome_nuovo_giocatore)) {
                setStato(GP_GESTIONE_PROFILI);
            }
            break;
    }
}

void Menu::cambiaVociMenuContinuaLivello() {
    switch (stato_attivo + CONTINUA_LIVELLO * 10) {
        case CL_CONTINUA:
            gioco->setStato(GIOCATORE);
            break;
        case CL_SALVA_LIVELLO:
            gestore_giocatori->salvaLivelloGiocatore();
            gioco->setStato(GIOCATORE);
            break;
        case CL_TORNA_A_MENU_PRINCIPALE:
            setStato(PRINCIPALE);
            break;
    }
}