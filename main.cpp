/* 
 * File:   main.cpp
 * Author: tonegas
 *
 * Created on 19 ottobre 2009, 22.41
 */

#include "include/Domino.h"

int main(int argc, char** argv) {
    Gioco domino;
    domino.loop();
    SDL_Quit();
    return (EXIT_SUCCESS);
}
