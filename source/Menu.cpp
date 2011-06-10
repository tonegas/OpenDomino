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

    stringa_stato_giocatore = (QStringList) "gioca" + (QStringList) "costruisce" + (QStringList) "prova";

    nuovo_nome = "";

    menu_centrale.setCarattere(font, &layout);
    menu_laterale.setCarattere(font, &layout);
    menu_voci_dinamiche.setCarattere(font, &layout);
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
    stato_cambio_posticipato = nuovo_stato;
    switch (nuovo_stato) {
        case TORNA_INDIETRO:
            switch (stato) {
                case GL_CAMBIA_LIVELLO:
                    setStato(GL_GIOCA_LIVELLO);
                    break;
                case EL_CAMBIA_LIVELLO:
                case EL_SALVA_LIVELLO_CON_NOME:
                    setStato(EL_EDITOR_LIVELLO);
                    break;
                case GEL_NUOVO_LIVELLO:
                case GEL_SCEGLI_LIVELLO:
                case GEL_ELIMINA_LIVELLO:
                case CONFERMA_ELIMINA_LIVELLO_SCELTO:
                    setStato(GESTIONE_LIVELLI);
                    break;
                default:
                    setStato(PRINCIPALE);
                    break;
            }
            break;
        case PRINCIPALE:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Open Domino");
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
            switch (gioco->getStatoGiocatore()) {
                case PARTITA:
                    setStatoCambioPosticipato(GL_GIOCA_LIVELLO);
                    break;
                case EDITOR_COSTRUISCI:
                    setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
                    break;
                case EDITOR_TEST:
                    setStatoCambioPosticipato(ELP_EDITOR_LIVELLO_PROVA);
                    break;
            }
            break;
        case SCEGLI_LIVELLO:
        case GL_CAMBIA_LIVELLO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Scegli livello");
            menu_attuale->inserisci(gestore_giocatori->listaLivelliGiocatore(), LIVELLO_SCELTO_PARTITA);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case LIVELLO_SCELTO_PARTITA:
            if (gestore_giocatori->cambiaLivelloGiocatore(menu_attuale->getStringa(), LIVELLO_PARTITA)) {
                setStatoCambioPosticipato(GL_GIOCA_LIVELLO);
                gioco->setStatoGiocatore(PARTITA);
                gioco->setStato(GIOCATORE);
            }
            break;
        case GESTIONE_LIVELLI:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Editor livelli");
            menu_attuale->inserisci("Nuovo livello", GEL_NUOVO_LIVELLO);
            menu_attuale->inserisci("Scegli livello", GEL_SCEGLI_LIVELLO);
            menu_attuale->inserisci("Elimina livello", GEL_ELIMINA_LIVELLO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case GEL_NUOVO_LIVELLO:
            menu_attuale = &menu_voci_dinamiche;
            menu_attuale->tipo = MENU_VOCI_DINAMICHE;
            nuovo_nome.clear();
            dim_x_nuovo_livello.clear();
            dim_y_nuovo_livello.clear();
            menu_attuale->azzera();
            menu_attuale->inserisci("Scegli caratteristiche livello");
            menu_attuale->inserisci("Nome livello", VUOTA, true, false);
            menu_attuale->inserisci("", &nuovo_nome, NOME_LIVELLO, true);
            menu_attuale->inserisci("Larghezza livello: ", &dim_x_nuovo_livello, GEL_NL_DIMX_LIVELLO, true);
            menu_attuale->inserisci("Altrzza livello: ", &dim_y_nuovo_livello, GEL_NL_DIMY_LIVELLO, true);
            menu_attuale->inserisci("Crea livello", GEL_NL_CREA_LIVELLO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case GEL_NL_CREA_LIVELLO:
            if (gestore_giocatori->nuovoLivelloGiocatore(nuovo_nome, dim_x_nuovo_livello.toUInt(), dim_y_nuovo_livello.toUInt())) {
                setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
                gioco->setStatoGiocatore(EDITOR_COSTRUISCI);
                gioco->setStato(GIOCATORE);
            }
            break;
        case GEL_SCEGLI_LIVELLO:
        case EL_CAMBIA_LIVELLO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Scegli livello");
            menu_attuale->inserisci(gestore_giocatori->listaLivelliGiocatore(), LIVELLO_SCELTO_EDITOR);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case GEL_ELIMINA_LIVELLO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Elimina livello");
            menu_attuale->inserisci(gestore_giocatori->listaLivelliGiocatore(), CONFERMA_ELIMINA_LIVELLO_SCELTO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case CONFERMA_ELIMINA_LIVELLO_SCELTO:
            livello_da_eliminare = menu_attuale->getStringa();
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Eliminazione livello");
            menu_attuale->inserisci(livello_da_eliminare, VUOTA, true, false);
            menu_attuale->inserisci("Conferma eliminazione", ELIMINA_LIVELLO_SCELTO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case ELIMINA_LIVELLO_SCELTO:
            if (gestore_giocatori->eliminaLivello(livello_da_eliminare)) {
                setStato(GESTIONE_LIVELLI);
            }
            break;
        case LIVELLO_SCELTO_EDITOR:
            if (gestore_giocatori->cambiaLivelloGiocatore(menu_attuale->getStringa(), LIVELLO_EDITOR)) {
                setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
                gioco->setStatoGiocatore(EDITOR_COSTRUISCI);
                gioco->setStato(GIOCATORE);
            }
            break;
        case GESTIONE_PROFILI:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Gestore Profili");
            menu_attuale->inserisci("Nuovo profilo", GP_NUOVO_PROFILO);
            menu_attuale->inserisci("Cambia profilo", GP_CAMBIA_PROFILO);
            menu_attuale->inserisci("Copia profilo attuale", GP_COPIA_PROFILO_ATTUALE);
            menu_attuale->inserisci("Elimina livello", GP_ELIMINA_PROFILO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case GP_NUOVO_PROFILO:
            menu_attuale = &menu_voci_dinamiche;
            menu_attuale->tipo = MENU_VOCI_DINAMICHE;
            nuovo_nome.clear();
            menu_attuale->azzera();
            menu_attuale->inserisci("Nuovo profilo");
            menu_attuale->inserisci("", &nuovo_nome, NOME_PROFILO, false);
            menu_attuale->inserisci("Crea profilo", GP_NP_CREA_PROFILO);
            menu_attuale->inserisci("Torna indierto", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case GP_NP_CREA_PROFILO:
            if (gestore_giocatori->nuovoGiocatore(nuovo_nome)) {
                setStato(PRINCIPALE);
            }
            break;
        case GP_COPIA_PROFILO_ATTUALE:
            menu_attuale = &menu_voci_dinamiche;
            menu_attuale->tipo = MENU_VOCI_DINAMICHE;
            nuovo_nome.clear();
            menu_attuale->azzera();
            menu_attuale->inserisci("Inserisci nome del profilo");
            menu_attuale->inserisci("", &nuovo_nome, NOME_PROFILO, false);
            menu_attuale->inserisci("Crea copia del profilo", GP_CPA_CREA_PROFILO);
            menu_attuale->inserisci("Torna indierto", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case GP_CPA_CREA_PROFILO:
            if (gestore_giocatori->copiaGiocatoreAttuale(nuovo_nome)) {
                setStato(GESTIONE_PROFILI);
            }
            break;
        case GP_CAMBIA_PROFILO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Cambia profilo");
            menu_attuale->inserisci(gestore_giocatori->nomiGiocatori(), PROFILO_SCELTO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case PROFILO_SCELTO:
            if (gestore_giocatori->cambiaGiocatore(menu_attuale->getStringa())) {
                setStato(PRINCIPALE);
            }
            break;
        case GP_ELIMINA_PROFILO:
            menu_attuale = &menu_laterale;
            menu_attuale->tipo = MENU_LATERALE_SCORRIMENTO;
            menu_attuale->azzera();
            menu_attuale->inserisci("Elimina profilo");
            menu_attuale->inserisci(gestore_giocatori->nomiGiocatori(), CONFERMA_ELIMINA_PROFILO_SCELTO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            resize();
            break;
        case CONFERMA_ELIMINA_PROFILO_SCELTO:
            profilo_da_eliminare = menu_attuale->getStringa();
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Eliminazione profilo");
            menu_attuale->inserisci(profilo_da_eliminare, VUOTA, true, false);
            menu_attuale->inserisci("Conferma eliminazione", ELIMINA_PROFILO_SCELTO);
            menu_attuale->inserisci("Torna al menu", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case ELIMINA_PROFILO_SCELTO:
            gestore_giocatori->eliminaGiocatore(profilo_da_eliminare);
            setStato(GESTIONE_PROFILI);
            break;
        case EL_EDITOR_LIVELLO:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Open Domino");
            menu_attuale->inserisci("Prova livello", EL_PROVA_LIVELLO);
            menu_attuale->inserisci("Salva livello", EL_SALVA_LIVELLO);
            menu_attuale->inserisci("Salve livello con nome", EL_SALVA_LIVELLO_CON_NOME);
            menu_attuale->inserisci("Cambia livello", EL_CAMBIA_LIVELLO);
            menu_attuale->inserisci("Torna al menu principale", TORNA_INDIETRO);
            resize();
            break;
        case EL_PROVA_LIVELLO:
            gioco->setStato(GIOCATORE);
            gioco->setStatoGiocatore(EDITOR_TEST);
            setStatoCambioPosticipato(ELP_EDITOR_LIVELLO_PROVA);
            break;
        case EL_SALVA_LIVELLO:
            gestore_giocatori->salvaLivelloGiocatore();
            gioco->setStato(GIOCATORE);
            break;
        case EL_SALVA_LIVELLO_CON_NOME:
            menu_attuale = &menu_voci_dinamiche;
            menu_attuale->tipo = MENU_VOCI_DINAMICHE;
            nuovo_nome.clear();
            menu_attuale->azzera();
            menu_attuale->inserisci("Salva livello con nome");
            menu_attuale->inserisci("", &nuovo_nome, NOME_LIVELLO, false);
            menu_attuale->inserisci("Salva livello", EL_SALVA_LIVELLO);
            menu_attuale->inserisci("Torna indierto", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case EL_SLCN_SALVA_LIVELLO:
            if (gestore_giocatori->salvaLivelloConNomeGiocatore(nuovo_nome)) {
                gioco->setStato(GIOCATORE);
            }
            break;
        case GL_GIOCA_LIVELLO:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Open Domino");
            menu_attuale->inserisci("Salva livello", GL_SALVA_LIVELLO, false, false);
            menu_attuale->inserisci("Cambia livello", GL_CAMBIA_LIVELLO);
            menu_attuale->inserisci("Torna al menu principale", TORNA_INDIETRO);
            menu_attuale->setVoceSelezionata(1);
            resize();
            break;
        case ELP_EDITOR_LIVELLO_PROVA:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Open Domino");
            menu_attuale->inserisci("Torna all'editor", ELP_TORNA_EDITOR);
            menu_attuale->inserisci("Torna al menu principale", TORNA_INDIETRO);
            resize();
            break;
        case ELP_TORNA_EDITOR:
            gioco->setStato(GIOCATORE);
            gioco->setStatoGiocatore(EDITOR_COSTRUISCI);
            setStatoCambioPosticipato(EL_EDITOR_LIVELLO);
            break;
        case PAUSA:
            menu_attuale = &menu_centrale;
            menu_attuale->tipo = MENU_CENTRALE;
            menu_attuale->azzera();
            menu_attuale->inserisci("Open Domino");
            menu_attuale->inserisci("Pausa", VUOTA, true, false);
            resize();
            break;
        case ESCI:
            gioco->gameExit();
            break;
        default:
            cout << "ERRORE DI INDIRIZZAMENTO MENU\n" << flush;
            break;
    }
    stato = nuovo_stato;
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
                        break;
                    case SDLK_DOWN:
                        menu_attuale->incrementoSelezione();
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
                                    setStato(TORNA_INDIETRO);
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
                                    case NOME_LIVELLO:
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
                            case GP_NUOVO_PROFILO:
                            case GP_COPIA_PROFILO_ATTUALE:
                            case EL_SALVA_LIVELLO_CON_NOME:
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
    menu_attuale->stampa();
    stampaGiocatoreAttuale();
    menu_attuale->aggiorna();
}

void Menu::cambiaVociMenu() {
    setStato(menu_attuale->statoSelezionato());
}

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
    if (stato_cambio_posticipato != stato) {
        setStato(stato_cambio_posticipato);
    }
}

void Menu::setStatoCambioPosticipato(StatoMenu nuovo_stato) {
    stato_cambio_posticipato = nuovo_stato;
}

void Menu::stampaGiocatoreAttuale() {
    font->FaceSize(dim_nome);
    layout.SetAlignment(FTGL::ALIGN_RIGHT);
    layout.SetLineLength(dim_x_fin - dist_da_destra_nome);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRasterPos2i(0, dim_y_fin - dist_da_alto_nome);
    layout.Render((gestore_giocatori->getNomeGiocatoreAttuale()
            + ' ' + stringa_stato_giocatore[gioco->getStatoGiocatore()]
            + ' ' + gestore_giocatori->getnomeLivelloAttuale()).toStdString().c_str());
}