/* 
 * File:   GestoreLivelli.cpp
 * Author: tonegas
 * 
 * Created on 6 dicembre 2009, 14.36
 */

#include "../include/Domino.h"

GestoreLivelli::GestoreLivelli() {
    cout << "Costruttore GestoreLivelli\n";
    file_livello = NULL;
    livello = NULL;
    QDir cartella = QDir::current();
    if (!cartella.cd("Livelli")) {
        cartella.mkdir("Livelli");
    }
}

void GestoreLivelli::apriFileLiv() {
    if (!file_livello->open(QIODevice::ReadWrite)) {
        cout << "ERRORE Aperetua File Giocatore\n";
        //FUNZIONE-DI-USCITA
    }
}

void GestoreLivelli::chiudiFileLiv() {
    file_livello->close();
}

void GestoreLivelli::eliminaFileLiv() {
    file_livello->remove();
}

GestoreLivelli::~GestoreLivelli() {
    //poi bisognera capire come va cancellato strutturaLivello
}

void GestoreLivelli::salvaFileLivello() {
    cout << "Salvo file livello:" << livello->nome_livello.toStdString() << '\n';
    eliminaFileLiv();
    apriFileLiv();
    QDomDocument doc("Livelli");
    QDomElement root = doc.createElement("Livello");
    root.setAttribute((QString) "nome", livello->nome_livello);
    doc.appendChild(root);
    QDomElement griglia = doc.createElement("Griglia");
    griglia.setAttribute((QString) "dim_x", livello->griglia_livello->getDimGrigliaX());
    griglia.setAttribute((QString) "dim_y", livello->griglia_livello->getDimGrigliaY());
    ElementoAttivo *testa = livello->griglia_livello->getTestaElementi();
    while (testa) {
        if (testa->elem != NULL) {
            QDomElement elemento = doc.createElement("Elemento");
            elemento.setAttribute((QString) "x", testa->x);
            elemento.setAttribute((QString) "y", testa->y);
            elemento.setAttribute((QString) "tipo", (unsigned) testa->tipo);
            griglia.appendChild(elemento);
        }
        testa = testa->next;
    }
    root.appendChild(griglia);
    QDomElement telecamera = doc.createElement("Telecamera");
    telecamera.setAttribute((QString) "tipo", livello->tipo_proiezione);
    root.appendChild(telecamera);
    QDomElement tele_prospettica = doc.createElement("TeleProspettica");
    tele_prospettica.setAttribute((QString) "x", livello->posizione_telecamere.telecamera_prospettica.x);
    tele_prospettica.setAttribute((QString) "y", livello->posizione_telecamere.telecamera_prospettica.y);
    tele_prospettica.setAttribute((QString) "z", livello->posizione_telecamere.telecamera_prospettica.z);
    tele_prospettica.setAttribute((QString) "ang_x", livello->posizione_telecamere.telecamera_prospettica.ang_x);
    tele_prospettica.setAttribute((QString) "ang_y", livello->posizione_telecamere.telecamera_prospettica.ang_y);
    telecamera.appendChild(tele_prospettica);
    QDomElement tele_assionometrica = doc.createElement("TeleAssionometrica");
    tele_assionometrica.setAttribute((QString) "x", livello->posizione_telecamere.telecamera_assionometrica.x);
    tele_assionometrica.setAttribute((QString) "y", livello->posizione_telecamere.telecamera_assionometrica.y);
    tele_assionometrica.setAttribute((QString) "zoom", livello->posizione_telecamere.telecamera_assionometrica.zoom);
    telecamera.appendChild(tele_assionometrica);
    QTextStream scriviFile(file_livello);
    scriviFile << doc.toString();
    chiudiFileLiv();
}

void fileBackupLivelli(QString file) {
    if (QFile::exists("Livelli/" + file + "_BACKUP.xml")) {
        QFile::remove("Livelli/" + file + "_BACKUP.xml");
    }
    QFile::copy("Livelli/" + file + ".xml", "Livelli/" + file + "_BACKUP.xml");
}

bool GestoreLivelli::caricaFileLivello() {
    cout << "Carico file livello\n";
    QDir cartella = QDir::current();
    cartella.cd("Livelli");
    QDomDocument doc("Livelli");
    apriFileLiv();
    if (!doc.setContent(file_livello)) {
        cout << "ERRORE file sbagliato\n";
        fileBackupLivelli(livello->nome_livello);
        eliminaFileLiv();
        return false;
    } else {
        cout << "Esiste Livello\n" << flush;
        QDomElement root = doc.documentElement();
        if (root.tagName() != "Livello") {
            cout << "ERRORE nome livello non presente\n";
            fileBackupLivelli(livello->nome_livello);
            eliminaFileLiv();
            return false;
        } else {
            livello->nome_livello = root.attribute("nome", "");
            if (livello->nome_livello != "") {
                QDomNode figlio = root.firstChild();
                if (!figlio.isNull()) {
                    QDomElement griglia = figlio.toElement();
                    if (!griglia.isNull() && griglia.tagName() == "Griglia") {
                        unsigned dim_x = griglia.attribute("dim_x", 0).toUInt();
                        unsigned dim_y = griglia.attribute("dim_y", 0).toUInt();
                        if (dim_x != 0 && dim_y != 0) {
                            livello->griglia_livello = new Griglia(dim_x, dim_y);
                            QDomElement elemento = griglia.firstChildElement();
                            while (!elemento.isNull()) {
                                if (elemento.tagName() == "Elemento") {
                                    unsigned x = elemento.attribute("x", "").toUInt();
                                    unsigned y = elemento.attribute("y", "").toUInt();
                                    unsigned tipo = elemento.attribute("tipo", "").toUInt();
                                    if (!livello->griglia_livello->creaElemento(x, y, (TipoElemento) tipo)) {
                                        cout << "ERRORE elemento non corretto\n";
                                        fileBackupLivelli(livello->nome_livello);
                                        eliminaFileLiv();
                                        return false;
                                    }
                                } else {
                                    cout << "ERRORE elemento tipo sbagliato\n";
                                    fileBackupLivelli(livello->nome_livello);
                                    eliminaFileLiv();
                                    return false;
                                }
                                elemento = elemento.nextSiblingElement();
                            }
                        } else {
                            cout << "ERRORE dimenzioni griglia errate\n";
                            fileBackupLivelli(livello->nome_livello);
                            eliminaFileLiv();
                            return false;
                        }
                    } else {
                        cout << "ERRORE griglia non presente\n";
                        fileBackupLivelli(livello->nome_livello);
                        eliminaFileLiv();
                        return false;
                    }
                } else {
                    cout << "ERRORE figlio livello non presente\n";
                    fileBackupLivelli(livello->nome_livello);
                    eliminaFileLiv();
                    return false;
                }
                figlio = figlio.nextSibling();
                if (!figlio.isNull()) {
                    QDomElement telecamera = figlio.toElement();
                    if (!telecamera.isNull() && telecamera.tagName() == "Telecamera") {
                        livello->tipo_proiezione = (Proiezione) telecamera.attribute("tipo", "").toUInt();
                        QDomElement tele = telecamera.firstChildElement();
                        while (!tele.isNull()) {
                            if (tele.tagName() == "TeleProspettica") {
                                livello->posizione_telecamere.telecamera_prospettica.x = tele.attribute("x", 0).toFloat();
                                livello->posizione_telecamere.telecamera_prospettica.y = tele.attribute("y", 0).toFloat();
                                livello->posizione_telecamere.telecamera_prospettica.z = tele.attribute("z", 0).toFloat();
                                livello->posizione_telecamere.telecamera_prospettica.ang_x = tele.attribute("ang_x", 0).toFloat();
                                livello->posizione_telecamere.telecamera_prospettica.ang_y = tele.attribute("ang_y", 0).toFloat();
                            }
                            if (tele.tagName() == "TeleAssionometrica") {
                                livello->posizione_telecamere.telecamera_assionometrica.x = tele.attribute("x", 0).toFloat();
                                livello->posizione_telecamere.telecamera_assionometrica.y = tele.attribute("y", 0).toFloat();
                                livello->posizione_telecamere.telecamera_assionometrica.zoom = tele.attribute("zoom", 0).toFloat();
                            }
                            tele = tele.nextSiblingElement();
                        }
                    } else {
                        cout << "ERRORE telecamera non presente\n";
                        fileBackupLivelli(livello->nome_livello);
                        eliminaFileLiv();
                        return false;
                    }
                } else {
                    cout << "ERRORE figlio livello non presente\n";
                    fileBackupLivelli(livello->nome_livello);
                    eliminaFileLiv();
                    return false;
                }
                chiudiFileLiv();
                return true;
            } else {
                fileBackupLivelli(livello->nome_livello);
                eliminaFileLiv();
                return false;
            }
        }
    }
}

void GestoreLivelli::creaFileLivello() {
    cout << "Creo file livello:" << livello->nome_livello.toStdString() << '\n' << flush;
    apriFileLiv();
    QDomDocument doc("Livelli");
    QDomElement root = doc.createElement("Livello");
    root.setAttribute((QString) "nome", livello->nome_livello);
    doc.appendChild(root);
    QDomElement griglia = doc.createElement("Griglia");
    griglia.setAttribute((QString) "dim_x", livello->griglia_livello->getDimGrigliaX());
    griglia.setAttribute((QString) "dim_y", livello->griglia_livello->getDimGrigliaY());
    root.appendChild(griglia);
    QDomElement telecamera = doc.createElement("Telecamera");
    telecamera.setAttribute((QString) "tipo", livello->tipo_proiezione);
    root.appendChild(telecamera);
    QTextStream scriviFile(file_livello);
    scriviFile << doc.toString();
    chiudiFileLiv();
}

bool GestoreLivelli::caricaLivello(QString nome_livello, StrutturaLivello* livello_aux) {
    cout << "Carico livello attuale:" << nome_livello.toStdString() << '\n' << flush;
    QFile aux("Livelli/" + nome_livello + ".xml");
    if (!aux.exists()) {
        return false;
    }
    livello = livello_aux;
    file_livello = new QFile("Livelli/" + nome_livello + ".xml");
    if (caricaFileLivello()) {
        delete file_livello;
        return true;
    } else {
        delete file_livello;
        return false;
    }
}

bool GestoreLivelli::nuovoLivello(StrutturaLivello* livello_aux) {
    livello = livello_aux;
    cout << "Nuovo livello, attuale: " << livello->nome_livello.toStdString() << '\n' << flush;
    file_livello = new QFile("Livelli/" + livello->nome_livello + ".xml");
    if (file_livello->exists()) {
        return false;
    }
    salvaFileLivello();
    delete file_livello;
    return true;
}

bool GestoreLivelli::copiaLivello(QString old_nome_livello, QString new_nome_livello) {
    if (old_nome_livello != "" && new_nome_livello != "") {
        cout << "Copia livello:" << old_nome_livello.toStdString() << " in " << new_nome_livello.toStdString() << '\n' << flush;
        QFile aux("Livelli/" + new_nome_livello + ".xml");
        if (aux.exists()) {
            return false;
        }
        if (file_livello != NULL) {
            delete file_livello;
        }
        file_livello = new QFile("Livelli/" + old_nome_livello + ".xml");
        if (!caricaFileLivello()) {
            return false;
        }
        livello->nome_livello = new_nome_livello;
        delete file_livello;
        file_livello = new QFile("Livelli/" + new_nome_livello + ".xml");
        salvaFileLivello();
        delete file_livello;
        return true;
    } else {
        return false;
    }
}

bool GestoreLivelli::eliminaLivello(QString nome_livello) {
    cout << "Elimina livello:" << nome_livello.toStdString() << '\n' << flush;
    if (QFile::exists("Livelli/" + nome_livello + ".xml")) {
        QFile::remove("Livelli/" + nome_livello + ".xml");
        return true;
    } else {
        return false;
    }
}

void GestoreLivelli::salvaLivello(StrutturaLivello* livello_aux) {
    livello = livello_aux;
    cout << "Salvo livello attuale:" << livello->nome_livello.toStdString() << '\n' << flush;
    file_livello = new QFile("Livelli/" + livello->nome_livello + ".xml");
    salvaFileLivello();
    delete file_livello;
}

QStringList GestoreLivelli::nomiLivelli() {
    QStringList nomi_livelli;
    QDir cartella = QDir::current();
    cartella.cd("Livelli");
    int num = cartella.count();
    for (int i = 0; i < num; i++) {
        QFile file("./Livelli/" + cartella[i]);
        QDomDocument doc("Livelli"); //<!DOCTYPE GiocatoreAttuale SYSTEM ".giocatori.dtd">
        if (!file.open(QIODevice::ReadOnly)) {
            cout << "ERRORE Aperetua File Giocatore\n";
            //FUNZIONE-DI-USCITA
        }
        if (doc.setContent(&file)) {
            QDomElement root = doc.documentElement();
            if (root.tagName() == "Livello") {
                QString nome = root.attribute("nome", "");
                if (nome + ".xml" == cartella[i]) {
                    nomi_livelli.append(nome);
                }
            }
        } else {
            cout << "File Tipo Sbagliato " << file.fileName().toStdString() << '\n' << flush;
        }
        file.close();
    }
    cout << nomi_livelli.count();
    return nomi_livelli;
}