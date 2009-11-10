/* 
 * File:   Texture.h
 * Author: tonegas
 *
 * Created on 9 novembre 2009, 10.43
 */

#ifndef _TEXTURE_H
#define	_TEXTURE_H

#define NUMERO_TEXTURES 10

enum Tex {
    TEX_PEZZO, TEX_BASE
};

using std::string;

#include "Domino.h"

class Texture {
protected:
    static unsigned numero_textures;
    static SDL_Surface* texture[NUMERO_TEXTURES];
    static GLuint indice_texture[NUMERO_TEXTURES];
public:
    Texture();
    ~Texture();
    static void loadTextures(string nome_immagine, Tex numero_tex_caricate);
};
#endif	/* _TEXTURE_H */

