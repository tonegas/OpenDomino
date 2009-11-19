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
bool Texture::inizializzata = false;

Texture::Texture() {
}

Texture::~Texture() {
    glDeleteTextures( NUMERO_TEXTURES, &indice_texture[0] );
}

void Texture::loadTextures(string nome_immagine, Tex numero_tex_caricate) {
    if ((Texture::texture[numero_tex_caricate] = SDL_LoadBMP(nome_immagine.c_str()))) {
        cout << "nome immagine:" << nome_immagine.c_str() << '\n' << flush;
        //1: numero di textures
        //2: indice nel vettore di textures

        cout << "numero textures:" << Texture::numero_textures << '\n' << flush;
        if (inizializzata == false) {
            glGenTextures(Texture::numero_textures, &Texture::indice_texture[0]);
            inizializzata = true;
        }
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

         int imageSize_RGB  = Texture::texture[numero_tex_caricate]->w * Texture::texture[numero_tex_caricate]->h * 3;
        int imageSize_RGBA = Texture::texture[numero_tex_caricate]->w * Texture::texture[numero_tex_caricate]->h * 4;

        // allocate buffer for a RGBA image
        unsigned char *pImage_RGBA = new unsigned char[imageSize_RGBA];

        //
        // Loop through the original RGB image buffer and copy it over to the
        // new RGBA image buffer setting each pixel that matches the key color
        // transparent.
        //
        int g_keyColor[3] = { 255, 0, 255 };
        int i, j;

        unsigned char* p=(unsigned char*)Texture::texture[numero_tex_caricate]->pixels;


        for( i = 0, j = 0; i < imageSize_RGB; i += 3, j += 4 )
        {
                    //cout<<'\"'<<(int)p[i]<<','<<(int)p[i+1]<<','<<(int)p[i+2]<<"\"\n"<<flush;
//            // Does the current pixel match the selected color key?
            if( p[i]   == g_keyColor[0] &&
                p[i+1] == g_keyColor[1] &&
                p[i+2] == g_keyColor[2] )
            {
                pImage_RGBA[j+3] = 0;   // If so, set alpha to fully transparent.
            }
            else
            {
                pImage_RGBA[j+3] = 255; // If not, set alpha to fully opaque.
            }

            pImage_RGBA[j]   = p[i];
            pImage_RGBA[j+1] = p[i+1];
            pImage_RGBA[j+2] = p[i+2];
        }


//        SDL_SetColorKey(Texture::texture[numero_tex_caricate], SDL_SRCCOLORKEY, SDL_MapRGB(Texture::texture[numero_tex_caricate]->format, COLORKEY));
//        SDL_Surface *aux = SDL_CreateRGBSurface(SDL_SWSURFACE, Texture::texture[numero_tex_caricate]->w, Texture::texture[numero_tex_caricate]->h, 24,
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//                0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
//#else
//                0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
//#endif
//        SDL_BlitSurface(Texture::texture[numero_tex_caricate], NULL, aux, NULL);

//        SDL_Surface* aux = SDL_DisplayFormatAlpha(Texture::texture[numero_tex_caricate]);
//        SDL_SetColorKey(aux,SDL_SRCCOLORKEY, SDL_MapRGB(aux->format, COLORKEY));

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texture::texture[numero_tex_caricate]->w,
                Texture::texture[numero_tex_caricate]->h, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, pImage_RGBA);

        /* Linear Filtering */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(Texture::texture[numero_tex_caricate]);
//        SDL_FreeSurface(aux);
        fprintf(stderr, "Errore: %s\n", gluErrorString(glGetError()));
    } else {
        printf("ERRORE di caricamento immagine SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}