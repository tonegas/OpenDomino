/* 
 * File:   Texture.cpp
 * Author: tonegas
 * 
 * Created on 9 novembre 2009, 10.43
 */

#include "../include/Domino.h"


unsigned Texture::numero_textures = NUMERO_TEXTURES;
SDL_Surface* Texture::texture[NUMERO_TEXTURES];
GLuint Texture::indice_texture[NUMERO_TEXTURES];

Texture::Texture() {
}

Texture::~Texture() {
}

void Texture::loadTextures(string nome_immagine, Tex numero_tex_caricate) {
    if ((Texture::texture[numero_tex_caricate] = SDL_LoadBMP(nome_immagine.c_str()))) {
        cout << "nome immagine:" << nome_immagine.c_str() << '\n' << flush;
        //1: numero di textures
        //2: indice nel vettore di textures

        cout << "numero textures:" << Texture::numero_textures << '\n' << flush;
        glGenTextures(Texture::numero_textures, &Texture::indice_texture[0]);
        /* Typical Texture Generation Using Data From The Bitmap */
        //1: sempre così
        //2: spazio della texture
        cout << "indice textures di zero:" << Texture::indice_texture[0] << '\n' << flush;
        glBindTexture(GL_TEXTURE_2D, Texture::indice_texture[numero_tex_caricate]);
        cout << "indice textures:" << Texture::indice_texture[numero_tex_caricate] << '\n' << flush;
        /* Generate The Texture */
        //1:così
        //2: 0
        //3:GL_ALPHA,GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA
        //4:larghezza
        //5:altezza
        //6:0
        //7:GL_ALPHA,GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA
        /* Generate The Texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Texture::texture[numero_tex_caricate]->w,
                Texture::texture[numero_tex_caricate]->h, 0, GL_BGR,
                GL_UNSIGNED_BYTE, Texture::texture[numero_tex_caricate]->pixels);

        /* Linear Filtering */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        fprintf(stderr, "Errore: %s\n", gluErrorString(glGetError()));
    } else {
        printf("ERRORE di caricamento immagine SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
    glBindTexture(GL_TEXTURE_2D,0);
}