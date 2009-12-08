/* 
 * File:   Texture.h
 * Author: tonegas
 *
 * Created on 9 novembre 2009, 10.43
 */

#ifndef _TEXTURES_H
#define	_TEXTURES_H

#define NUMERO_TEXTURES 10

enum Tex {
    TEX_PEZZO, TEX_BASE, TEX_NUVOLA1, TEX_NUVOLA2,
};

struct TexWH{
    unsigned int w,h;
};

using std::string;

#include "Domino.h"

class Textures {
protected:
    static bool inizializzata;
    static unsigned numero_textures;
    static GLuint indice_texture[NUMERO_TEXTURES];
    static TexWH struttura_texture[NUMERO_TEXTURES];
public:
    Textures();
    ~Textures();
    static void pulisci();
    static void loadTextures(string nome_immagine, Tex numero_tex_caricate,int* key_color, bool gradiente=false);
    static void loadTextures(string nome_immagine, Tex numero_tex_caricate);
};
#endif	/* _TEXTURES_H */

