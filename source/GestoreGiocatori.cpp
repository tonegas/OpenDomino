/* 
 * File:   GestoreGiocatori.cpp
 * Author: tonegas
 * 
 * Created on 4 dicembre 2009, 16.39
 */

#include "../include/Domino.h"

GestoreGiocatori::GestoreGiocatori() : file_giocatore_attuale("Giocatori/.giocatoreAttuale.xml") {
    cout << "Costruttore GestoreGiocatori\n";
    giocatore_attuale = NULL;
    file_giocatore = NULL;
    QDir cartella = QDir::current();
    if (!cartella.cd("Giocatori")) {
        cartella.mkdir("Giocatori");
    }
    if (!file_giocatore_attuale.exists()) {
        creaFileGiocatoreAttuale();
    }
    caricaFileGiocatoreAttuale();
    file_giocatore = new QFile("Giocatori/" + nome_giocatore_attuale + ".xml");
    if (!file_giocatore->exists()) {
        creaFileGiocatore();
    }
    caricaFileGiocatore();
}

void GestoreGiocatori::apriFileGioAttuale() {
    if (!file_giocatore_attuale.open(QIODevice::ReadWrite)) {
        cout << "ERRORE Aperetua File";
        //FUNZIONE-DI-USCITA
    }
}

void GestoreGiocatori::chiudiFileGioAttuale() {
    file_giocatore_attuale.close();
}

void GestoreGiocatori::eliminaFileGioAttuale() {
    file_giocatore_attuale.remove();
}

void GestoreGiocatori::apriFileGio() {
    if (!file_giocatore->open(QIODevice::ReadWrite)) {
        cout << "ERRORE Aperetua File Giocatore";
        //FUNZIONE-DI-USCITA
    }
}

void GestoreGiocatori::chiudiFileGio() {
    file_giocatore->close();
}

void GestoreGiocatori::eliminaFileGio() {
    file_giocatore->remove();
}

GestoreGiocatori::~GestoreGiocatori() {
    cout << "Comincio chiusura\n";
    chiudiFileGioAttuale();
    salvaFileGiocatore();
    if (file_giocatore != NULL) {
        chiudiFileGio();
        delete file_giocatore;
    }
    delete giocatore_attuale;
    //    for (int i = 0; i < lista.size(); i++) {
    //        cout << lista[i]->getNome().toStdString();
    //        delete lista[i];
    //    }
}

void GestoreGiocatori::creaFileGiocatoreAttuale(QString nome_giocatore) {
    cout << "Creo file giocatore attuale:" << nome_giocatore.toStdString() << '\n';
    apriFileGioAttuale();
    QDomDocument doc("GiocatoreAttuale");
    QDomElement root = doc.createElement("Attivo");
    root.setAttribute((QString) "nome", nome_giocatore);
    doc.appendChild(root);
    QTextStream scriviFile(&file_giocatore_attuale);
    scriviFile << doc.toString();
    chiudiFileGioAttuale();
}

void fileBackup(QString file) {
    if (QFile::exists("Giocatori/" + file + "_BACKUP.xml")) {
        QFile::remove("Giocatori/" + file + "_BACKUP.xml");
    }
    QFile::copy("Giocatori/" + file + ".xml", "Giocatori/" + file + "_BACKUP.xml");
}

void GestoreGiocatori::caricaFileGiocatoreAttuale() {
    cout << "Carico file giocatore attuale\n" << flush;
    QDir cartella = QDir::current();
    cartella.cd("Giocatori");
    QDomDocument doc("GiocatoreAttuale"); //<!DOCTYPE GiocatoreAttuale SYSTEM ".giocatori.dtd">
    apriFileGioAttuale();
    if (!doc.setContent(&file_giocatore_attuale)) {
        cout << "ERRORE file sbagliato\n";
        fileBackup(".giocatoreAttuale");
        eliminaFileGioAttuale();
        creaFileGiocatoreAttuale();
        caricaFileGiocatoreAttuale();
    } else {
        cout << "Esiste\n" << flush;
        QDomElement root = doc.documentElement();
        if (root.tagName() != "Attivo") {
            cout << "ERRORE nome giocatore non presente\n";
            fileBackup(".giocatoreAttuale");
            eliminaFileGioAttuale();
            creaFileGiocatoreAttuale();
            caricaFileGiocatoreAttuale();
        } else {
            QString nome = root.attribute("nome", "");
            if (nome != "") {
                cout << "Giocatore attuale:" << nome.toStdString() << '\n' << flush;
                //se il file giocatore è già aperto lo devo chiudere e poi deallocare
                nome_giocatore_attuale = nome;
                chiudiFileGioAttuale();
            } else {
                fileBackup(".giocatoreAttuale");
                eliminaFileGioAttuale();
                creaFileGiocatoreAttuale();
                caricaFileGiocatoreAttuale();
            }
        }
    }
}

void GestoreGiocatori::creaFileGiocatore() {
    cout << "Creo file giocatore:" << nome_giocatore_attuale.toStdString() << '\n';
    apriFileGio();
    QDomDocument doc("Giocatori");
    QDomElement root = doc.createElement("Giocatore");
    root.setAttribute((QString) "nome", nome_giocatore_attuale);
    root.setAttribute((QString) "data_di_creazione", (int) time(NULL));
    root.setAttribute((QString) "tempo_di_gioco", 0);
    doc.appendChild(root);
    QTextStream scriviFile(file_giocatore);
    scriviFile << doc.toString();
    chiudiFileGio();
}

//questa funzione dovrà uscire ogni volta che c'è errore
//in maniera da poter presentare un messaggio di errore fuori
//queste chiamate qui dovranno essere in una funzione
/*        fileBackup(nome_giocatore_attuale);
        eliminaFileGio();
        creaFileGiocatore();
        caricaFileGiocatore();
 */
//stessa cosa per caricaFileGiocatoreAttuale()

void GestoreGiocatori::caricaFileGiocatore() {
    cout << "Carico file giocatore\n";
    QDir cartella = QDir::current();
    cartella.cd("Giocatori");
    QDomDocument doc("Giocatori"); //<!DOCTYPE GiocatoreAttuale SYSTEM ".giocatori.dtd">
    apriFileGio();
    if (!doc.setContent(file_giocatore)) {
        cout << "ERRORE file sbagliato\n";
        fileBackup(nome_giocatore_attuale);
        eliminaFileGio();
        creaFileGiocatore();
        caricaFileGiocatore();
    } else {
        cout << "Esiste Giocatore\n" << flush;
        QDomElement root = doc.documentElement();
        if (root.tagName() != "Giocatore") {
            cout << "ERRORE nome giocatore non presente";
            fileBackup(nome_giocatore_attuale);
            eliminaFileGio();
            creaFileGiocatore();
            caricaFileGiocatore();
        } else {
            QString nome = root.attribute("nome", "");
            QString data_di_creazione = root.attribute("data_di_creazione", "");
            QString tempo_di_gioco = root.attribute("tempo_di_gioco", "");
            if (nome == nome_giocatore_attuale && data_di_creazione != "" && tempo_di_gioco != "") {
                if (giocatore_attuale != NULL) {
                    delete giocatore_attuale;
                }
                giocatore_attuale = new Giocatore(nome, tempo_di_gioco.toLong(), data_di_creazione.toLong());
                giocatore_attuale->inizializzaTutto();
                //lista.append(giocatore_attuale);
                cout << "Caricato giocatore:" << nome.toStdString() << '\n' << flush;
                chiudiFileGio();
            } else {
                fileBackup(nome_giocatore_attuale);
                eliminaFileGio();
                creaFileGiocatore();
                caricaFileGiocatore();
            }
        }
    }
}

void GestoreGiocatori::salvaFileGiocatore() {
    cout << "Salvo giocatore:" << giocatore_attuale->getNome().toStdString() << '\n' << flush;
    apriFileGio();
    QDomDocument doc("Giocatori");
    QDomElement root = doc.createElement("Giocatore");
    root.setAttribute((QString) "nome", giocatore_attuale->getNome());
    root.setAttribute((QString) "data_di_creazione", (int) giocatore_attuale->getDataDiCreazione());
    root.setAttribute((QString) "tempo_di_gioco", (int) giocatore_attuale->getTempoDiGioco()+((int) time(NULL)-(int) giocatore_attuale->getTempoDiGiocoApertura()));
    doc.appendChild(root);
    QTextStream scriviFile(file_giocatore);
    scriviFile << doc.toString();
    chiudiFileGio();
}

//la funzione cambia giocatore se è lo stesso giocatore non deve fare niente
//se viene chiamata su in giocatore inisistente non va a buon fine

bool GestoreGiocatori::cambiaGiocatore(QString nome_giocatore) {
    cout << "Cambio giocatore attuale:" << nome_giocatore_attuale.toStdString() << " in " << nome_giocatore.toStdString() << '\n' << flush;
    QFile aux("Giocatori/" + nome_giocatore + ".xml");
    if (!aux.exists()) {
        return false;
    }
    if (nome_giocatore_attuale != nome_giocatore) {
        salvaFileGiocatore();
        nome_giocatore_attuale = nome_giocatore;
        delete file_giocatore;
        file_giocatore = new QFile("Giocatori/" + nome_giocatore_attuale + ".xml");
        caricaFileGiocatore();
        eliminaFileGioAttuale();
        creaFileGiocatoreAttuale(nome_giocatore_attuale);
    }
    return true;
}

//se viene chiamata su un giocatore che esiste gia non va a buon fine

bool GestoreGiocatori::nuovoGiocatore(QString nome_giocatore) {
    if (nome_giocatore != "") {
        cout << "Nuovo giocatore, attuale:" << nome_giocatore_attuale.toStdString() << " in " << nome_giocatore.toStdString() << '\n' << flush;
        QFile aux("Giocatori/" + nome_giocatore + ".xml");
        if (aux.exists()) {
            return false;
        }
        salvaFileGiocatore();
        nome_giocatore_attuale = nome_giocatore;
        delete file_giocatore;
        file_giocatore = new QFile("Giocatori/" + nome_giocatore_attuale + ".xml");
        creaFileGiocatore();
        caricaFileGiocatore();
        eliminaFileGioAttuale();
        creaFileGiocatoreAttuale(nome_giocatore_attuale);
        return true;
    } else {
        return false;
    }
}

bool GestoreGiocatori::copiaGiocatoreAttuale(QString nome_giocatore) {
    if (nome_giocatore != "") {
        cout << "Copia giocatore attuale:" << nome_giocatore_attuale.toStdString() << " in " << nome_giocatore.toStdString() << '\n' << flush;
        QFile aux("Giocatori/" + nome_giocatore + ".xml");
        if (aux.exists()) {
            return false;
        }
        Giocatore giocatore_aux = (*giocatore_attuale);
        giocatore_attuale->setNome(nome_giocatore);
        nome_giocatore_attuale = nome_giocatore;
        delete file_giocatore;
        file_giocatore = new QFile("Giocatori/" + nome_giocatore_attuale + ".xml");
        salvaFileGiocatore();
        cambiaGiocatore(giocatore_aux.getNome());
        return true;
    } else {
        return false;
    }
}

bool GestoreGiocatori::eliminaGiocatore(QString nome_giocatore) {
    cout << "Elimina giocatore:" << nome_giocatore.toStdString() << '\n' << flush;
    if (nome_giocatore_attuale == nome_giocatore) {
        eliminaGiocatore();
        return true;
    } else {
        if (QFile::exists("Giocatori/" + nome_giocatore + ".xml")) {
            QFile::remove("Giocatori/" + nome_giocatore + ".xml");
            return true;
        } else {
            return false;
        }
    }
}

void GestoreGiocatori::eliminaGiocatore() {
    cout << "Elimina giocatore attuale:" << nome_giocatore_attuale.toStdString() << '\n' << flush;
    nome_giocatore_attuale = "__DOMINO__";
    eliminaFileGio();
    delete file_giocatore;
    file_giocatore = new QFile("Giocatori/" + nome_giocatore_attuale + ".xml");
    if (!file_giocatore->exists()) {
        creaFileGiocatore();
    }
    caricaFileGiocatore();
    eliminaFileGioAttuale();
    creaFileGiocatoreAttuale(nome_giocatore_attuale);
}

void GestoreGiocatori::salvaGiocatore() {
    cout << "Salvo giocatore attuale:" << nome_giocatore_attuale.toStdString() << '\n' << flush;
    salvaFileGiocatore();
    giocatore_attuale->setTempoDiGiocoApertura();
}

QString GestoreGiocatori::nomeGiocatoreAttuale() {
    if (giocatore_attuale->getNome() != "__DOMINO__")
        return giocatore_attuale->getNome();
    return "";
}

QStringList GestoreGiocatori::nomiGiocatori() {
    QStringList nomi_giocatori;
    QDir cartella = QDir::current();
    cartella.cd("Giocatori");
    int num = cartella.count();
    for (int i = 0; i < num; i++) {
        QFile file("./Giocatori/" + cartella[i]);
        QDomDocument doc("Giocatori"); //<!DOCTYPE GiocatoreAttuale SYSTEM ".giocatori.dtd">
        if (!file.open(QIODevice::ReadOnly)) {
            cout << "ERRORE Aperetua File Giocatore";
            //FUNZIONE-DI-USCITA
        }
        if (doc.setContent(&file)) {
            QDomElement root = doc.documentElement();
            if (root.tagName() == "Giocatore") {
                QString nome = root.attribute("nome", "");
                if (nome + ".xml" == cartella[i] && nome != "__DOMINO__") {
                    nomi_giocatori.append(nome);
                }
            }
        } else {
            cout << "File Tipo Sbagliato " << file.fileName().toStdString() << '\n' << flush;
        }
        file.close();
    }
    return nomi_giocatori;
}

Giocatore** GestoreGiocatori::getGiocatoreAttuale() {
    return &giocatore_attuale;
}
