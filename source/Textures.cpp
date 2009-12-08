/* 
 * File:   Texture.cpp
 * Author: tonegas
 * 
 * Created on 9 novembre 2009, 10.43
 */

#include "../include/Domino.h"


unsigned Textures::numero_textures = NUMERO_TEXTURES;
GLuint Textures::indice_texture[NUMERO_TEXTURES];
TexWH Textures::struttura_texture[NUMERO_TEXTURES];
bool Textures::inizializzata = false;

Textures::Textures() {
}

Textures::~Textures() {
}

void Textures::pulisci(){
    glDeleteTextures(NUMERO_TEXTURES, &indice_texture[0]);
}

void Textures::loadTextures(string nome_immagine, Tex numero_tex_caricate) {
    SDL_Surface *tex;
    if ((tex = SDL_LoadBMP(nome_immagine.c_str()))) {
        cout << "nome immagine:" << nome_immagine.c_str() << '\n' << flush;
        //1: numero di textures
        //2: indice nel vettore di textures

        cout << "numero textures:" << Textures::numero_textures << '\n' << flush;
        if (inizializzata == false) {
            glGenTextures(Textures::numero_textures, &Textures::indice_texture[0]);
            inizializzata = true;
        }
        /* Typical Texture Generation Using Data From The Bitmap */
        //1: sempre così
        //2: spazio della texture
        cout << "indice textures di zero:" << Textures::indice_texture[0] << '\n' << flush;
        glBindTexture(GL_TEXTURE_2D, Textures::indice_texture[numero_tex_caricate]);
        cout << "indice textures:" << Textures::indice_texture[numero_tex_caricate] << '\n' << flush;
        /* Generate The Texture */
        //1:così
        //2: 0
        //3:GL_ALPHA,GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA
        //4:larghezza
        //5:altezza
        //6:0
        //7:GL_ALPHA,GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA
        /* Generate The Texture */
        struttura_texture[numero_tex_caricate].w = tex->w;
        struttura_texture[numero_tex_caricate].h = tex->h;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w,
                tex->h, 0, GL_RGB,
                GL_UNSIGNED_BYTE, tex->pixels);

        /* Linear Filtering */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(tex);
        fprintf(stderr, "Errore: %s\n", gluErrorString(glGetError()));
    } else {
        printf("ERRORE di caricamento immagine SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Textures::loadTextures(string nome_immagine, Tex numero_tex_caricate, int* key_color, bool gradiente) {
    SDL_Surface *tex;
    if ((tex = SDL_LoadBMP(nome_immagine.c_str()))) {
        cout << "nome immagine:" << nome_immagine.c_str() << '\n' << flush;
        //1: numero di textures
        //2: indice nel vettore di textures

        cout << "numero textures:" << Textures::numero_textures << '\n' << flush;
        if (inizializzata == false) {
            glGenTextures(Textures::numero_textures, &Textures::indice_texture[0]);
            inizializzata = true;
        }
        /* Typical Texture Generation Using Data From The Bitmap */
        //1: sempre così
        //2: spazio della texture
        cout << "indice textures di zero:" << Textures::indice_texture[0] << '\n' << flush;
        glBindTexture(GL_TEXTURE_2D, Textures::indice_texture[numero_tex_caricate]);
        cout << "indice textures:" << Textures::indice_texture[numero_tex_caricate] << '\n' << flush;
        /* Generate The Texture */
        //1:così
        //2: 0
        //3:GL_ALPHA,GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA
        //4:larghezza
        //5:altezza
        //6:0
        //7:GL_ALPHA,GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA
        /* Generate The Texture */
        struttura_texture[numero_tex_caricate].w = tex->w;
        struttura_texture[numero_tex_caricate].h = tex->h;
        int texture_size_RGB = tex->w * tex->h * 3;
        int texture_size_RGBA = tex->w * tex->h * 4;

        // allocate buffer for a RGBA image
        unsigned char *texture_RGBA = new unsigned char[texture_size_RGBA];

        unsigned char* p = (unsigned char*) tex->pixels;

        for (int i = 0, j = 0; i < texture_size_RGB; i += 3, j += 4) {
            texture_RGBA[j] = p[i + 2];
            texture_RGBA[j + 1] = p[i + 1];
            texture_RGBA[j + 2] = p[i];
            if (gradiente) {
                //max distanza 441
                texture_RGBA[j + 3] = sqrt(((int) p[i] - key_color[2])*((int) p[i] - key_color[2])
                        +((int) p[i + 1] - key_color[1])*((int) p[i + 1] - key_color[1])
                        +((int) p[i + 2] - key_color[0])*((int) p[i + 2] - key_color[0])) > 260 ?
                        255 : sqrt(((int) p[i] - key_color[2])*((int) p[i] - key_color[2])
                        +((int) p[i + 1] - key_color[1])*((int) p[i + 1] - key_color[1])
                        +((int) p[i + 2] - key_color[0])*((int) p[i + 2] - key_color[0])) / 260 * 255;
            } else {
                if (p[i] == key_color[2] && p[i + 1] == key_color[1] && p[i + 2] == key_color[0]) {
                    texture_RGBA[j + 3] = 0;
                } else {
                    texture_RGBA[j + 3] = 255;
                }
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w,
                tex->h, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, texture_RGBA);

        /* Linear Filtering */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(tex);
        delete []texture_RGBA;
        //        SDL_FreeSurface(aux);
        fprintf(stderr, "Errore: %s\n", gluErrorString(glGetError()));
    } else {
        printf("ERRORE di caricamento immagine SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}