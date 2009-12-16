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

    voci_menu_gel_nuovo_livello.append("Nome livello: ");
    voci_menu_gel_nuovo_livello.append("Dimensione X: ");
    voci_menu_gel_nuovo_livello.append("Dimensione Y: ");
    voci_menu_gel_nuovo_livello.append("Crea livello");
    voci_menu_gel_nuovo_livello.append("Torna indietro");
    voci_menu_gel_nuovo_livello.append("Nuovo livello");

    voci_menu_gel_scegli_livello.append("Torna indietro");
    voci_menu_gel_scegli_livello.append("Scegli livello");

    voci_menu_gel_elimina_livello.append("Torna indietro");
    voci_menu_gel_elimina_livello.append("Elimina livello");

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

    pausa.append("Pausa");
    pausa.append("Open Domino");

    nuovo_nome = "";

    menu_centrale.setCarattere(font, &layout);
    menu_laterale.setCarattere(font, &layout);
    menu_voci_dinamiche.setCarattere(font, &layout);

    setStato(PRINCIPALE);
}

void Menu::resize() {
    if (dim_x_fin >= 1000 && dim_y_fin >= 1000) {
        dist_da_destra_nome = 15;
        dist_da_alto_nome = 35;
        dim_nome = 30;
    } else {
        if (dim_x_fin > dim_y_fin) {
            dist_da_destra_nome = (float) dim_y_fin / 500.0 * 7;
            dist_da_alto_nome = (float) dim_y_fin / 500.0 * 17;
            dim_nome = (float) dim_y_fin / 500.0 * 15;
        } else {
            dist_da_destra_nome = (float) dim_x_fin / 500.0 * 7;
            dist_da_alto_nome = (float) dim_x_fin / 500.0 * 17;
            dim_nome = (float) dim_x_fin / 500.0 * 15;
        }
    }
    menu_attuale->resize(dim_x_fin, dim_y_fin);
}

void Menu::resize(unsigned dim_x, unsigned dim_y) {
    dim_x_fin = dim_x;
    dim_y_fin = dim_y;
    resize();
}

void Menu::setStato(StatoMenu nuovo_stato) {
    //   stato_cambio_posticipato = nuovo_stato;
    stato = nuovo_stato;
    switch (stato) {
        case TORNA_INDIETRO:
            setStato(PRINCIPALE);
            break;
        case PRINCIPALE:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Open Domino", PRINCIPALE);
            if ((*gestore_giocatori->getGiocatoreAttuale())->getNomeLivello() != "Intro") {
                menu_attuale->inserisci("Continua Partita", CONTINUA_PARTITA);
            }
            menu_attuale->inserisci("Scegli Livello", SCEGLI_LIVELLO);
            menu_attuale->inserisci("Editor livelli", GESTIONE_LIVELLI);
            menu_attuale->inserisci("Opzioni", OPZIONI, false, false);
            menu_attuale->inserisci("Gestione profili", GESTIONE_PROFILI);
            menu_attuale->inserisci("Istruzioni", ISTRUZIONI, false, false);
            menu_attuale->inserisci("Ringraziamenti", RINGRAZIAMENTI, false, false);
            menu_attuale->inserisci("Esci", ESCI);
            resize();
            break;
        case CONTINUA_PARTITA:
            gioco->setStato(GIOCATORE);
            break;
        case SCEGLI_LIVELLO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Scegli livello", SCEGLI_LIVELLO);
            menu_attuale->inserisci(gestore_giocatori->listaLivelliGiocatore(), SL_LIVELLO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case SL_LIVELLO:
            if (gestore_giocatori->cambiaLivelloGiocatore(menu_attuale->getStringa(), LIVELLO_PARTITA)) {
                setStato(GL_GIOCA_LIVELLO);
                gioco->setStato(GIOCATORE);
            }
            break;
        case GESTIONE_LIVELLI:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Editor livelli", GESTIONE_LIVELLI);
            menu_attuale->inserisci("Nuovo livello", GEL_NUOVO_LIVELLO);
            menu_attuale->inserisci("Scegli livello", GEL_SCEGLI_LIVELLO);
            menu_attuale->inserisci("Elimina livello", GEL_ELIMINA_LIVELLO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case GEL_NUOVO_LIVELLO:
            menu_attuale = &menu_voci_dinamiche;
            menu_attuale->tipo = MENU_VOCI_DINAMICHE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Scegli caratteristiche livello", GEL_NUOVO_LIVELLO);
            menu_attuale->inserisci("Nome livello",VUOTA, true, false);
            menu_attuale->inserisci("", &nuovo_nome, GEL_NL_NOME_LIVELLO, true);
            menu_attuale->inserisci("Larghezza livello: ", &dim_x_nuovo_livello, GEL_NL_DIMX_LIVELLO, true);
            menu_attuale->inserisci("Altrzza livello: ", &dim_y_nuovo_livello, GEL_NL_DIMY_LIVELLO, true);
            menu_attuale->inserisci("Crea livello", GEL_NL_CREA_LIVELLO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
            //            menu_attuale = &menu_crea_livello;
            //            menu_attuale->tipo = MENU_CREA_LIVELLO;
            //            menu_attuale->azzera();
            //            menu_attuale->inserisci("Editor livelli", GESTIONE_LIVELLI);
            //            menu_attuale->inserisci("Nuovo livello", GEL_NUOVO_LIVELLO);
            //            menu_attuale->inserisci("Scegli livello", GEL_SCEGLI_LIVELLO);
            //            menu_attuale->inserisci("Elimina livello", GEL_ELIMINA_LIVELLO);
            //            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            //            resize();
            //            setStato(GEL_NL_NUOVO_LIVELLO);
            //            nuovo_nome.clear();
            //            dim_x_nuovo_livello = "100";
            //            dim_y_nuovo_livello = "100";
            //            if (gestore_giocatori->nuovoLivelloGiocatore(nuovo_nome, dim_x_nuovo_livello.toUInt(), dim_y_nuovo_livello.toUInt())) {
            //                setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
            //                gioco->setStato(GIOCATORE);
            //            }
        case GEL_SCEGLI_LIVELLO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Scegli livello", GEL_SCEGLI_LIVELLO);
            menu_attuale->inserisci(gestore_giocatori->listaLivelliGiocatore(), GEL_SL_LIVELLO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case GEL_SL_LIVELLO:
            if (gestore_giocatori->cambiaLivelloGiocatore(menu_attuale->getStringa(), LIVELLO_EDITOR)) {
                setStato(EL_EDITOR_LIVELLO);
                gioco->setStato(GIOCATORE);
            }
            break;
        case ESCI:
            gioco->gameExit();
            break;
        default:
            cout << "ERRORE DI INDIRIZZAMENTO MENU\n" << flush;
            break;
    }

    //            inizializzaVariabiliMenu(G_GIOCA, voci_menu_gioca);
    //            costruisciCaselleMenuCentrale();

    //        case G_SL_SCEGLI_LIVELLO:
    //            inizializzaVariabiliMenu(G_SL_SCEGLI_LIVELLO,
    //                    (QStringList) voci_menu_g_scegli_livello[0] + lista_livelli + (QStringList) voci_menu_g_scegli_livello[1], lista_livelli.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //            //--------------------------
    //        case GEL_GESTIONE_LIVELLI:
    //            inizializzaVariabiliMenu(GEL_GESTIONE_LIVELLI, voci_menu_gestione_livelli);
    //            costruisciCaselleMenuCentrale();
    //            break;
    //        case GEL_NL_NUOVO_LIVELLO:
    //            inizializzaVariabiliMenu(GEL_NL_NUOVO_LIVELLO, voci_menu_gel_nuovo_livello);
    //            costruisciCaselleMenuCentrale();
    //            break;
    //        case GEL_SL_SCEGLI_LIVELLO:
    //            inizializzaVariabiliMenu(GEL_SL_SCEGLI_LIVELLO,
    //                    (QStringList) voci_menu_gel_scegli_livello[0] + lista_livelli + (QStringList) voci_menu_gel_scegli_livello[1], lista_livelli.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //        case GEL_EL_ELIMINA_LIVELLO:
    //            inizializzaVariabiliMenu(GEL_EL_ELIMINA_LIVELLO,
    //                    (QStringList) voci_menu_gel_elimina_livello[0] + lista_livelli + (QStringList) voci_menu_gel_elimina_livello[1], lista_livelli.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //            //--------------------------
    //        case GP_GESTIONE_PROFILI:
    //            inizializzaVariabiliMenu(GP_GESTIONE_PROFILI, voci_menu_gestione_profili);
    //            costruisciCaselleMenuCentrale();
    //            break;
    //        case GP_NP_NUOVO_PROFILO:
    //            inizializzaVariabiliMenu(GP_NP_NUOVO_PROFILO, voci_menu_gp_nuovo_profilo + (QStringList) nuovo_nome);
    //            costruisciCaselleMenuCrea();
    //            break;
    //        case GP_CP_CAMBIA_PROFILO:
    //            inizializzaVariabiliMenu(GP_CP_CAMBIA_PROFILO,
    //                    (QStringList) voci_menu_gp_cambia_profilo[0] + nomi_giocatori + (QStringList) voci_menu_gp_cambia_profilo[1], nomi_giocatori.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //        case GP_EL_ELIMINA_PROFILO:
    //            inizializzaVariabiliMenu(GP_EL_ELIMINA_PROFILO,
    //                    (QStringList) voci_menu_gp_elimina_profilo[0] + nomi_giocatori + (QStringList) voci_menu_gp_elimina_profilo[1], nomi_giocatori.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //        case GP_CPA_COPIA_PROFILO_ATTUALE:
    //            inizializzaVariabiliMenu(GP_CPA_COPIA_PROFILO_ATTUALE, voci_menu_gp_copia_profilo_attuale + (QStringList) nuovo_nome);
    //            costruisciCaselleMenuCrea();
    //            break;
    //            //:::::::::::::::::::::::::::::::::::
    //        case EL_EDITOR_LIVELLO:
    //            inizializzaVariabiliMenu(EL_EDITOR_LIVELLO, voci_menu_el_editor_livello);
    //            costruisciCaselleMenuCentrale();
    //            break;
    //        case EL_SLCN_SALVA_LIVELLO_CON_NOME:
    //            inizializzaVariabiliMenu(EL_SLCN_SALVA_LIVELLO_CON_NOME, voci_menu_el_salva_con_nome + (QStringList) nuovo_nome);
    //            costruisciCaselleMenuCrea();
    //            break;
    //        case EL_CL_CAMBIA_LIVELLO:
    //            inizializzaVariabiliMenu(EL_CL_CAMBIA_LIVELLO,
    //                    (QStringList) voci_menu_el_cambia_livello[0] + lista_livelli + (QStringList) voci_menu_el_cambia_livello[1], lista_livelli.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //            //:::::::::::::::::::::::::::::::::::
    //        case GL_GIOCA_LIVELLO:
    //            inizializzaVariabiliMenu(GL_GIOCA_LIVELLO, voci_menu_gl_gioca_livello);
    //            costruisciCaselleMenuCentrale();
    //            break;
    //        case GL_CL_CAMBIA_LIVELLO:
    //            inizializzaVariabiliMenu(GL_CL_CAMBIA_LIVELLO,
    //                    (QStringList) voci_menu_gl_cambia_livello[0] + lista_livelli + (QStringList) voci_menu_gl_cambia_livello[1], lista_livelli.count());
    //            costruisciCaselleMenuLaterale();
    //            break;
    //            //:::::::::::::::::::::::::::::::::::
    //        case ELP_EDITOR_LIVELLO_PROVA:
    //            inizializzaVariabiliMenu(ELP_EDITOR_LIVELLO_PROVA, voci_menu_elp_editor_livello_prova);
    //            costruisciCaselleMenuCentrale();
    //            break;
    //        case PAUSA:
    //            inizializzaVariabiliMenu(PAUSA, pausa);
    //            costruisciCaselleMenuCentrale();
    //            break;
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
                        menu_attuale->decrementoSelezione();
                        //--------------------------------
                        //                        stato_attivo = (stato_attivo - 1) >= numero_voci_menu_attivo ? (numero_voci_menu_attivo - 1) : (stato_attivo - 1);
                        //                        if (numero_voci_menu_attivo > voci_visibili) {
                        //                            switch (stato) {
                        //                                case GP_EL_ELIMINA_PROFILO:
                        //                                case GP_CP_CAMBIA_PROFILO:
                        //                                case G_SL_SCEGLI_LIVELLO:
                        //                                case GEL_SL_SCEGLI_LIVELLO:
                        //                                case GEL_EL_ELIMINA_LIVELLO:
                        //                                case EL_CL_CAMBIA_LIVELLO:
                        //                                case GL_CL_CAMBIA_LIVELLO:
                        ////                                    aggiornaStatoAttivoVociMenuLaterale();
                        ////                                    costruisciCaselleMenuLaterale();
                        //                                    break;
                        //                                default:
                        //                                    break;
                        //                            }
                        //                        }
                        //-------------------------------
                        break;
                    case SDLK_DOWN:
                        menu_attuale->incrementoSelezione();
                        //--------------------------------
                        //                        stato_attivo = ((stato_attivo + 1) % numero_voci_menu_attivo);
                        //                        if (numero_voci_menu_attivo > voci_visibili) {
                        //                            switch (stato) {
                        //                                case GP_EL_ELIMINA_PROFILO:
                        //                                case GP_CP_CAMBIA_PROFILO:
                        //                                case G_SL_SCEGLI_LIVELLO:
                        //                                case GEL_SL_SCEGLI_LIVELLO:
                        //                                case GEL_EL_ELIMINA_LIVELLO:
                        //                                case EL_CL_CAMBIA_LIVELLO:
                        //                                case GL_CL_CAMBIA_LIVELLO:
                        ////                                    aggiornaStatoAttivoVociMenuLaterale();
                        ////                                    costruisciCaselleMenuLaterale();
                        //                                    break;
                        //                                default:
                        //                                    break;
                        //                            }
                        //                        }
                        //--------------------------------
                        break;
                    case SDLK_RETURN:
                        cambiaVociMenu();
                        break;
                    case SDLK_ESCAPE:
                        if (stato != PRINCIPALE && stato != PAUSA) {
                            switch (stato) {
                                case EL_EDITOR_LIVELLO:
                                case GL_GIOCA_LIVELLO:
                                case ELP_EDITOR_LIVELLO_PROVA:
                                    gioco->setStato(GIOCATORE);
                                    break;
                                default:
                                    stato_attivo = (stato % (stato / 10 * 10)) - 1;
                                    cambiaVociMenu();
                                    break;
                            }
                        }
                        break;
                    default:
                        switch (stato) {
                            case PAUSA:
                                gioco->setStato(GIOCATORE);
                                break;
                            case GEL_NUOVO_LIVELLO:
                                switch (menu_attuale->statoSelezionato()) {
                                    case GEL_NL_NOME_LIVELLO:
                                        if (evento->key.keysym.sym <= SDLK_z && evento->key.keysym.sym >= SDLK_a && nuovo_nome.count() <= 30) {
                                            if (evento->key.keysym.mod & KMOD_SHIFT) {
                                                nuovo_nome += evento->key.keysym.sym - 32;
                                            } else {
                                                nuovo_nome += evento->key.keysym.sym;
                                            }
                                        }
                                        if (evento->key.keysym.sym == SDLK_BACKSPACE) {
                                            nuovo_nome.resize(nuovo_nome.count() - 1);
                                        }
                                        break;
                                    case GEL_NL_DIMX_LIVELLO:
                                        if (evento->key.keysym.sym <= SDLK_9 && evento->key.keysym.sym >= SDLK_0 && dim_x_nuovo_livello.count() < 4) {
                                            dim_x_nuovo_livello += evento->key.keysym.sym;
                                        }
                                        if (evento->key.keysym.sym == SDLK_BACKSPACE) {
                                            dim_x_nuovo_livello.resize(dim_x_nuovo_livello.count() - 1);
                                        }
                                        break;
                                    case GEL_NL_DIMY_LIVELLO:
                                        if (evento->key.keysym.sym <= SDLK_9 && evento->key.keysym.sym >= SDLK_0 && dim_y_nuovo_livello.count() < 4) {
                                            dim_y_nuovo_livello += evento->key.keysym.sym;
                                        }
                                        if (evento->key.keysym.sym == SDLK_BACKSPACE) {
                                            dim_y_nuovo_livello.resize(dim_y_nuovo_livello.count() - 1);
                                        }
                                        break;
                                    default:
                                        break;
                                }
                                break;
                                //                            case GP_NP_NUOVO_PROFILO:
                                //                            case GP_CPA_COPIA_PROFILO_ATTUALE:
                                //                            case EL_SLCN_SALVA_LIVELLO_CON_NOME:
                                //                                if (evento->key.keysym.sym <= SDLK_z && evento->key.keysym.sym >= SDLK_a && nuovo_nome.count() <= 30) {
                                //                                    if (evento->key.keysym.mod & KMOD_SHIFT) {
                                //                                        nuovo_nome += evento->key.keysym.sym - 32;
                                //                                    } else {
                                //                                        nuovo_nome += evento->key.keysym.sym;
                                //                                    }
                                //                                }
                                //                                if (evento->key.keysym.sym == SDLK_BACKSPACE) {
                                //                                    nuovo_nome.resize(nuovo_nome.count() - 1);
                                //                                }
                                //                                break;
                            default:
                                break;
                        }
                        break;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            menu_attuale->aggiornaMovimento(evento->motion.x, evento->motion.y);
            menu_attuale->gestisciSelezioneMouse(evento->motion.x, evento->motion.y);

            if (numero_voci_menu_attivo > voci_visibili) {
                switch (stato) {
                    case GP_EL_ELIMINA_PROFILO:
                    case GP_CP_CAMBIA_PROFILO:
                        //                    case G_SL_SCEGLI_LIVELLO:
                        //                    case GEL_SL_SCEGLI_LIVELLO:
                        //                    case GEL_EL_ELIMINA_LIVELLO:
                    case EL_CL_CAMBIA_LIVELLO:
                    case GL_CL_CAMBIA_LIVELLO:
                        //                        aggiornaStatoAttivoVociMenuLateraleMouse();
                        //                        costruisciCaselleMenuLaterale();
                        //                        gestisciSelezioneMouseMenuLaterale();
                        break;
                    default:
                        break;
                }
            } else {
                //                gestisciSelezioneMouse();
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (evento->button.button == SDL_BUTTON_LEFT)
                if (menu_attuale->gestisciSelezioneMouse(evento->motion.x, evento->motion.y)) {
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
    //    switch (stato) {
    //        case GP_EL_ELIMINA_PROFILO:
    //        case GP_CP_CAMBIA_PROFILO:
    //        case G_SL_SCEGLI_LIVELLO:
    //        case GEL_SL_SCEGLI_LIVELLO:
    //        case GEL_EL_ELIMINA_LIVELLO:
    //        case EL_CL_CAMBIA_LIVELLO:
    //        case GL_CL_CAMBIA_LIVELLO:
    //            stampaMenuLaterale();
    //            break;
    //        case GP_CPA_COPIA_PROFILO_ATTUALE:
    //        case GP_NP_NUOVO_PROFILO:
    //        case EL_SLCN_SALVA_LIVELLO_CON_NOME:
    //            stampaMenuInserisciParola();
    //            break;
    //        case GEL_NL_NUOVO_LIVELLO:
    //            stampaMenuCreaLivello();
    //            break;
    //        default:
    menu_attuale->stampa();
    //            //stampaMenuCentrale();
    //            break;
    //    }
    stampaGiocatoreAttuale();
    menu_attuale->aggiorna();
    //    aggiornaStatoAttivoVociMenu();
}

void Menu::cambiaVociMenu() {
    setStato(menu_attuale->statoSelezionato());
    //    switch (menu_attuale->statoSelezionato()) {
    //            //switch (stato_attivo + PRIMO * 10) {
    //        case ESCI:
    //            gioco->gameExit();
    //            break;
    //            case CONTINUA_PARTITA:
    //                gioco->setStato(GIOCATORE);
    //            break;
    //        case SCEGLI_LIVELLO:
    //            lista_livelli = gestore_giocatori->listaLivelliGiocatore();
    //            break;
    //            //            break;
    //            //        case GESTIONE_LIVELLI:
    //            //            setStato(GEL_GESTIONE_LIVELLI);
    //            //            break;
    //            //        case GESTIONE_PROFILI:
    //            //            setStato(GP_GESTIONE_PROFILI);
    //            //            break;
    //        default:
    //            break;
    //    }
    //    switch (stato) {
    //        case PRINCIPALE:
    //            cambiaVociMenuPrincipale();
    //            break;
    //        case G_GIOCA:
    //            cambiaVociMenuGioca();
    //            break;
    //        case G_SL_SCEGLI_LIVELLO:
    //            cambiaVociMenuGScegliLivello();
    //            break;
    //        case GEL_GESTIONE_LIVELLI:
    //            cambiaVociMenuGestioneLivelli();
    //            break;
    //        case GEL_NL_NUOVO_LIVELLO:
    //            cambiaVociMenuGeLNuovoLivello();
    //            break;
    //        case GEL_SL_SCEGLI_LIVELLO:
    //            cambiaVociMenuGeLScegliLivello();
    //            break;
    //        case GEL_EL_ELIMINA_LIVELLO:
    //            cambiaVociMenuGeLEliminaLivello();
    //            break;
    //        case GP_GESTIONE_PROFILI:
    //            cambiaVociMenuGestioneProfili();
    //            break;
    //        case GP_CP_CAMBIA_PROFILO:
    //            cambiaVociMenuGPCambiaProfilo();
    //            break;
    //        case GP_EL_ELIMINA_PROFILO:
    //            cambiaVociMenuGPEliminaProfilo();
    //            break;
    //        case GP_NP_NUOVO_PROFILO:
    //            cambiaVociMenuGPNuovoProfilo();
    //            break;
    //        case GP_CPA_COPIA_PROFILO_ATTUALE:
    //            cambiaVociMenuGPCopiaProfiloAttuale();
    //            break;
    //        case EL_EDITOR_LIVELLO:
    //            cambiaVociMenuELEditorLivelli();
    //            break;
    //        case EL_SLCN_SALVA_LIVELLO_CON_NOME:
    //            cambiaVociMenuELSalvaConNome();
    //            break;
    //        case EL_CL_CAMBIA_LIVELLO:
    //            cambiaVociMenuELCambiaLivello();
    //            break;
    //        case GL_GIOCA_LIVELLO:
    //            cambiaVociMenuGLGiocaLivello();
    //            break;
    //        case GL_CL_CAMBIA_LIVELLO:
    //            cambiaVociMenuGLCambiaLivello();
    //            break;
    //        case ELP_EDITOR_LIVELLO_PROVA:
    //            cambiaVociMenuELPEditorLivelloProva();
    //            break;
    //        default:
    //            break;
    //    }
}

void Menu::cambiaVociMenuPrincipale() {
    switch (menu_attuale->statoSelezionato()) {
            //switch (stato_attivo + PRIMO * 10) {
        case ESCI:
            gioco->gameExit();
            break;
            //        case GIOCA:
            //            setStato(G_GIOCA);
            break;
        case GESTIONE_LIVELLI:
            //            setStato(GEL_GESTIONE_LIVELLI);
            break;
        case GESTIONE_PROFILI:
            setStato(GP_GESTIONE_PROFILI);
            break;
        default:
            break;
    }
}

void Menu::cambiaVociMenuGioca() {
    //    switch (stato_attivo + GIOCA * 10) {
    //        case G_CONTINUA:
    //            setStatoCambioPosticipato(GL_GIOCA_LIVELLO);
    //            gioco->setStato(GIOCATORE);
    //            break;
    //        case G_SCEGLI_LIVELLO:
    //            lista_livelli = gestore_giocatori->listaLivelliGiocatore();
    //            setStato(G_SL_SCEGLI_LIVELLO);
    //            break;
    //        case G_TORNA_A_MENU_PRINCIPALE:
    //            setStato(PRINCIPALE);
    //            break;
    //    }
}

void Menu::cambiaVociMenuGScegliLivello() {
    //    switch (stato_attivo + G_SCEGLI_LIVELLO * 10) {
    //        case G_SL_TORNA_INDIETRO:
    //            setStato(G_GIOCA);
    //            break;
    //        default:
    //            if (gestore_giocatori->cambiaLivelloGiocatore(lista_livelli[stato_attivo - 1], LIVELLO_PARTITA)) {
    //                setStatoCambioPosticipato(GL_GIOCA_LIVELLO);
    //                gioco->setStato(GIOCATORE);
    //            }
    //            break;
    //    }
}

void Menu::cambiaVociMenuGestioneLivelli() {
    //    switch (stato_attivo + GESTIONE_LIVELLI * 10) {
    //        case GEL_NUOVO_LIVELLO:
    //            setStato(GEL_NL_NUOVO_LIVELLO);
    //            nuovo_nome.clear();
    //            dim_x_nuovo_livello = "100";
    //            dim_y_nuovo_livello = "100";
    //            break;
    //        case GEL_SCEGLI_LIVELLO:
    //            lista_livelli = gestore_giocatori->listaLivelliGiocatore();
    //            setStato(GEL_SL_SCEGLI_LIVELLO);
    //            break;
    //        case GEL_ELIMINA_LIVELLO:
    //            lista_livelli = gestore_giocatori->listaLivelliGiocatore();
    //            setStato(GEL_EL_ELIMINA_LIVELLO);
    //            break;
    //        case GEL_TORNA_A_MENU_PRINCIPALE:
    //            setStato(PRINCIPALE);
    //            break;
    //    }
}

void Menu::cambiaVociMenuGeLNuovoLivello() {
    //    switch (stato_attivo + GEL_NUOVO_LIVELLO * 10) {
    //        case GEL_NL_TORNA_INDIETRO:
    //            setStato(GEL_GESTIONE_LIVELLI);
    //            break;
    //        case GEL_NL_CREA_LIVELLO:
    //            setStato(GEL_NL_NUOVO_LIVELLO);
    //            nuovo_nome.clear();
    //            dim_x_nuovo_livello = "100";
    //            dim_y_nuovo_livello = "100";
    //            if (gestore_giocatori->nuovoLivelloGiocatore(nuovo_nome, dim_x_nuovo_livello.toUInt(), dim_y_nuovo_livello.toUInt())) {
    //                setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
    //                gioco->setStato(GIOCATORE);
    //            }
    //            break;
    //    }
}

void Menu::cambiaVociMenuGeLScegliLivello() {
    //    switch (stato_attivo + GEL_SCEGLI_LIVELLO * 10) {
    //        case GEL_SL_TORNA_INDIETRO:
    //            setStato(GEL_GESTIONE_LIVELLI);
    //            break;
    //        default:
    //            if (gestore_giocatori->cambiaLivelloGiocatore(lista_livelli[stato_attivo - 1], LIVELLO_EDITOR)) {
    //                setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
    //                gioco->setStato(GIOCATORE);
    //            }
    //            break;
    //    }
}

void Menu::cambiaVociMenuGeLEliminaLivello() {
    switch (stato_attivo + GEL_ELIMINA_LIVELLO * 10) {
            //        case GEL_EL_TORNA_INDIETRO:
            //            setStato(GEL_GESTIONE_LIVELLI);
            //            break;
            //        default:
            //??????????????????????????
            //            break;
    }
}

void Menu::cambiaVociMenuGestioneProfili() {
    switch (stato_attivo + GESTIONE_PROFILI * 10) {
        case GP_NUOVO_PROFILO:
            setStato(GP_NP_NUOVO_PROFILO);
            nuovo_nome.clear();
            break;
        case GP_CAMBIA_PROFILO:
            nomi_giocatori = gestore_giocatori->nomiGiocatori();
            setStato(GP_CP_CAMBIA_PROFILO);
            break;
        case GP_COPIA_PROFILO_ATTUALE:
            setStato(GP_CPA_COPIA_PROFILO_ATTUALE);
            nuovo_nome.clear();
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
        case GP_CP_TORNA_INDIETRO:
            setStato(GP_GESTIONE_PROFILI);
            break;
        default:
            if (gestore_giocatori->cambiaGiocatore(nomi_giocatori[stato_attivo - 1])) {
                setStato(PRINCIPALE);
            }
            break;
    }
}

void Menu::cambiaVociMenuGPEliminaProfilo() {
    //aggiungere una schermata dove si dice sicuro di voler eliminare il giocatore comic si no
    switch (stato_attivo + GP_ELIMINA_PROFILO * 10) {
        case GP_EL_TORNA_INDIETRO:
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
        case GP_NP_TORNA_INDIETRO:
            setStato(GP_GESTIONE_PROFILI);
            break;
        case GP_NP_CREA_PROFILO:
            if (gestore_giocatori->nuovoGiocatore(nuovo_nome)) {
                setStato(PRINCIPALE);
            }
            break;
    }
}

void Menu::cambiaVociMenuGPCopiaProfiloAttuale() {
    switch (stato_attivo + GP_COPIA_PROFILO_ATTUALE * 10) {
        case GP_CPA_TORNA_INDIETRO:
            setStato(GP_GESTIONE_PROFILI);
            break;
        case GP_CPA_CREA_COPIA_PROFILO:
            if (gestore_giocatori->copiaGiocatoreAttuale(nuovo_nome)) {
                setStato(GP_GESTIONE_PROFILI);
            }
            break;
    }
}

void Menu::cambiaVociMenuELEditorLivelli() {
    switch (stato_attivo + SECONDO * 10) {
        case EL_PROVA_LIVELLO:
            gioco->setStato(GIOCATORE);
            gioco->setStatoGiocatore(EDITOR_TEST);
            //            setStatoCambioPosticipato(ELP_EDITOR_LIVELLO_PROVA);
            break;
        case EL_SALVA_LIVELLO:
            gestore_giocatori->salvaLivelloGiocatore();
            gioco->setStato(GIOCATORE);
            break;
        case EL_SALVA_LIVELLO_CON_NOME:
            nuovo_nome.clear();
            setStato(EL_SLCN_SALVA_LIVELLO_CON_NOME);
            break;
        case EL_CAMBIA_LIVELLO:
            lista_livelli = gestore_giocatori->listaLivelliGiocatore();
            setStato(EL_CL_CAMBIA_LIVELLO);
            break;
        case EL_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE:
            setStato(PRINCIPALE);
            break;
    }
}

void Menu::cambiaVociMenuELSalvaConNome() {
    switch (stato_attivo + EL_SALVA_LIVELLO_CON_NOME * 10) {
        case EL_SLCN_TORNA_INDIETRO:
            setStato(EL_EDITOR_LIVELLO);
            break;
        case EL_SLCN_SALVA_LIVELLO:
            if (gestore_giocatori->salvaLivelloConNomeGiocatore(nuovo_nome)) {
                //                setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
                gioco->setStato(GIOCATORE);
            }
            break;
    }
}

void Menu::cambiaVociMenuELCambiaLivello() {
    switch (stato_attivo + EL_CAMBIA_LIVELLO * 10) {
        case EL_CL_TORNA_INDIETRO:
            setStato(GL_GIOCA_LIVELLO);
            break;
        default:
            if (gestore_giocatori->cambiaLivelloGiocatore(lista_livelli[stato_attivo - 1], LIVELLO_EDITOR)) {
                //                setStatoCambioPosticipato(GL_GIOCA_LIVELLO);
                gioco->setStato(GIOCATORE);
            }
            break;
    }
}

void Menu::cambiaVociMenuGLGiocaLivello() {
    switch (stato_attivo + TERZO * 10) {
        case GL_SALVA_LIVELLO:
            //?????????????????
            break;
        case GL_CAMBIA_LIVELLO:
            lista_livelli = gestore_giocatori->listaLivelliGiocatore();
            setStato(GL_CL_CAMBIA_LIVELLO);
            break;
        case GL_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE:
            setStato(PRINCIPALE);
            break;
    }
}

void Menu::cambiaVociMenuGLCambiaLivello() {
    switch (stato_attivo + GL_CAMBIA_LIVELLO * 10) {
        case GL_CL_TORNA_INDIETRO:
            setStato(GL_GIOCA_LIVELLO);
            break;
        default:
            if (gestore_giocatori->cambiaLivelloGiocatore(lista_livelli[stato_attivo - 1], LIVELLO_PARTITA)) {
                //                setStatoCambioPosticipato(GL_GIOCA_LIVELLO);
                gioco->setStato(GIOCATORE);
            }
            break;
    }
}

void Menu::cambiaVociMenuELPEditorLivelloProva() {
    switch (stato_attivo + QUARTO * 10) {
        case ELP_TORNA_EDITOR:
            setStato(EL_EDITOR_LIVELLO);
            gioco->setStatoGiocatore(EDITOR_COSTRUISCI);
            break;
        case ELP_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE:
            setStato(PRINCIPALE);
            break;
    }
}
