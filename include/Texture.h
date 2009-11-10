/* 
 * File:   Texture.h
 * Author: tonegas
 *
 * Created on 9 novembre 2009, 10.43
 */

#ifndef _TEXTURE_H
#define	_TEXTURE_H

#define NUMERO_TEXTURES 10

using std::string;

#include "Domino.h"

class Texture {
    static unsigned numero_textures;
    static unsigned numero_tex_caricate;
    static SDL_Surface* texture[NUMERO_TEXTURES];
    static GLuint indice_texture[NUMERO_TEXTURES];
public:
    Texture();
    ~Texture();
    static int loadTextures(string nome_immagine);
};
#endif	/* _TEXTURE_H */

