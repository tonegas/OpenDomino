/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include "include/Domino.h"
#include "include/Gioco.h"

int main() {
    Gioco domino;
    domino.loop();
    SDL_Quit();
    return (EXIT_SUCCESS);
}
