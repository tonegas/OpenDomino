/* 
 * File:   GestoreLivelli.cpp
 * Author: tonegas
 * 
 * Created on 6 dicembre 2009, 14.36
 */

#include "../include/Domino.h"

extern void fileBackup(QString file);

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
        cout << "ERRORE Aperetua File Giocatore";
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
    if (file_livello != NULL) {
        chiudiFileLiv();
        delete file_livello;
    }
    if (livello != NULL) {
        delete livello;
    }
}

void GestoreLivelli::salvaFileLivello() {
    cout << "Salvo file Livello:" << livello->nome_livello.toStdString() << '\n';
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
        QDomElement elemento = doc.createElement("Elemento");
        elemento.setAttribute((QString) "x", testa->x);
        elemento.setAttribute((QString) "y", testa->y);
        elemento.setAttribute((QString) "tipo", (unsigned) testa->tipo);
        griglia.appendChild(elemento);
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
    tele_assionometrica.setAttribute((QString) "y", livello->posizione_telecamere.telecamera_assionometrica.x);
    tele_assionometrica.setAttribute((QString) "zoom", livello->posizione_telecamere.telecamera_assionometrica.x);
    telecamera.appendChild(tele_assionometrica);
    QTextStream scriviFile(file_livello);
    scriviFile << doc.toString();
    chiudiFileLiv();
}

bool GestoreLivelli::caricaFileLivello() {
    cout << "Carico file livello\n";
    QDir cartella = QDir::current();
    cartella.cd("Livelli");
    QDomDocument doc("Livelli");
    apriFileLiv();
    if (!doc.setContent(file_livello)) {
        cout << "ERRORE file sbagliato\n";
        fileBackup(livello->nome_livello);
        eliminaFileLiv();
        return false;
    } else {
        cout << "Esiste Livello\n" << flush;
        QDomElement root = doc.documentElement();
        if (root.tagName() != "Livello") {
            cout << "ERRORE nome livello non presente";
            fileBackup(livello->nome_livello);
            eliminaFileLiv();
            return false;
        } else {
            if(livello != NULL){
                cout<<"ERRORE livello sempre occupato";
                return false;
            }
            livello = new StrutturaLivello();
            livello->nome_livello = root.attribute("nome", "");
            if (livello->nome_livello != "") {
                QDomNode figlio = root.firstChild();
                if (!figlio.isNull()) {
                    QDomElement griglia = figlio.toElement();
                    if (!griglia.isNull() && griglia.tagName() == "Griglia") {
                        unsigned dim_x = griglia.attribute("dim_x", 0).toUInt();
                        unsigned dim_y = griglia.attribute("dim_x", 0).toUInt();
                        if (dim_x != 0 && dim_y != 0) {
                            livello->griglia_livello = new Griglia(dim_x, dim_y);
                            QDomNode figlio_griglia = griglia.firstChild();
                            while (!figlio_griglia.isNull()) {
                                QDomElement elemento = griglia.toElement();
                                if (!elemento.isNull() && elemento.tagName() == "Elemento") {
                                    unsigned x = elemento.attribute("x", "").toUInt();
                                    unsigned y = elemento.attribute("y", "").toUInt();
                                    unsigned tipo = elemento.attribute("tipo", "").toUInt();
                                    if (!livello->griglia_livello->creaElemento(x, y, (TipoElemento) tipo)) {
                                        cout << "ERRORE elemento non corretto";
                                        fileBackup(livello->nome_livello);
                                        eliminaFileLiv();
                                        return false;
                                    }
                                } else {
                                    cout << "ERRORE elemento non presente";
                                    fileBackup(livello->nome_livello);
                                    eliminaFileLiv();
                                    return false;
                                }
                                figlio_griglia = figlio_griglia.nextSibling();
                            }
                        } else {
                            cout << "ERRORE dimenzioni griglia errate";
                            fileBackup(livello->nome_livello);
                            eliminaFileLiv();
                            return false;
                        }
                    } else {
                        cout << "ERRORE griglia non presente";
                        fileBackup(livello->nome_livello);
                        eliminaFileLiv();
                        return false;
                    }
                } else {
                    cout << "ERRORE figlio livello non presente";
                    fileBackup(livello->nome_livello);
                    eliminaFileLiv();
                    return false;
                }
                figlio = figlio.nextSibling();
                if (!figlio.isNull()) {
                    QDomElement telecamera = figlio.toElement();
                    if (!telecamera.isNull() && telecamera.tagName() == "Telecamera") {
                        livello->tipo_proiezione = (Proiezione) telecamera.attribute("tipo", "").toUInt();
                        QDomNode figlio_telecamera = telecamera.firstChild();
                        while (!figlio_telecamera.isNull()) {
                            QDomElement tele = figlio_telecamera.toElement();
                            if (!tele.isNull() && tele.tagName() == "TeleProspettica") {
                                livello->posizione_telecamere.telecamera_prospettica.x = tele.attribute("x", 0).toUInt();
                                livello->posizione_telecamere.telecamera_prospettica.y = tele.attribute("y", 0).toUInt();
                                livello->posizione_telecamere.telecamera_prospettica.z = tele.attribute("z", 0).toUInt();
                                livello->posizione_telecamere.telecamera_prospettica.ang_x = tele.attribute("ang_x", 0).toUInt();
                                livello->posizione_telecamere.telecamera_prospettica.ang_y = tele.attribute("ang_y", 0).toUInt();
                            }
                            if (!tele.isNull() && tele.tagName() == "TeleAssionometrica") {
                                livello->posizione_telecamere.telecamera_assionometrica.x = tele.attribute("x", 0).toUInt();
                                livello->posizione_telecamere.telecamera_assionometrica.y = tele.attribute("y", 0).toUInt();
                                livello->posizione_telecamere.telecamera_assionometrica.zoom = tele.attribute("zoom", 0).toUInt();
                            }
                            figlio_telecamera = figlio_telecamera.nextSibling();
                        }
                    } else {
                        cout << "ERRORE telecamera non presente";
                        fileBackup(livello->nome_livello);
                        eliminaFileLiv();
                        return false;
                    }
                } else {
                    cout << "ERRORE figlio livello non presente";
                    fileBackup(livello->nome_livello);
                    eliminaFileLiv();
                    return false;
                }
                chiudiFileLiv();
                return true;
            } else {
                fileBackup(livello->nome_livello);
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

bool GestoreLivelli::caricaLivello(QString nome_livello) {
    cout << "Carico Livello attuale:" << nome_livello.toStdString() << '\n' << flush;
    QFile aux("Livelli/" + nome_livello + ".xml");
    if (!aux.exists()) {
        return false;
    }
    if (file_livello != NULL) {
        delete file_livello;
    }
    file_livello = new QFile("Livelli/" + nome_livello + ".xml");
    if (caricaFileLivello()) {
        return true;
    } else {
        return false;
    }
}

bool GestoreLivelli::nuovoLivello(QString nome_livello, unsigned dim_x, unsigned dim_y) {
    if (nome_livello != "") {
        cout << "Nuovo Livello, attuale:" << livello->nome_livello.toStdString() << '\n' << flush;
        QFile aux("Livelli/" + livello->nome_livello + ".xml");
        if (aux.exists()) {
            return false;
        }
        if (livello != NULL) {
            delete livello;
        }
        livello = new StrutturaLivello();
        livello->nome_livello = nome_livello;
        livello->griglia_livello = new Griglia(dim_x, dim_y);
        if (file_livello != NULL) {
            delete file_livello;
        }
        file_livello = new QFile("Livelli/" + livello->nome_livello + ".xml");
        creaFileLivello();
        return true;
    } else {
        return false;
    }
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

void GestoreLivelli::salvaLivello() {
    cout << "Salvo Livello attuale:" << livello->nome_livello.toStdString() << '\n' << flush;
    salvaFileLivello();
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
            cout << "ERRORE Aperetua File Giocatore";
            //FUNZIONE-DI-USCITA
        }
        if (doc.setContent(&file)) {
            QDomElement root = doc.documentElement();
            if (root.tagName() == "Livelli") {
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
    return nomi_livelli;
}

StrutturaLivello* GestoreLivelli::getStrutturaLivello() {
    StrutturaLivello *aux =livello;
    livello = NULL;
    return aux;
}

void GestoreLivelli::setStrutturaLivello(StrutturaLivello* livello_aux) {
    livello = livello_aux;
}