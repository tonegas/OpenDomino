// -*- C++ -*-
/* 
 * File:   Domino.
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 23.51
 */

#ifndef _DOMINO_
#define	_DOMINO_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTBBox.h>
#include <FTGL/FTPoint.h>
#include <QFile>

#define PARAMETRO_NON_USATO(x) (void)x

using namespace std;

#include "Textures.h"
#include "Elemento.h"
#include "ElementoAttivo.h"
#include "basi/Base.h"
#include "pezzi/Pezzo.h"
#include "Griglia.h"
#include "PosTelecamere.h"
#include "Telecamera.h"
#include "TelecameraAssionometrica.h"
#include "TelecameraProspettica.h"
#include "Interfaccia.h"
#include "Livello.h"
#include "Partita.h"
#include "Presentazione.h"
#include "Editor.h"
#include "GestoreLivelli.h"
#include "Giocatore.h"
#include "GestoreGiocatori.h"
#include "MenuAttivo.h"
#include "MenuCentrale.h"
#include "MenuLaterale.h"
#include "MenuVociDinamiche.h"
#include "Menu.h"
#include "Gioco.h"


#endif	/* _DOMINO_ */

