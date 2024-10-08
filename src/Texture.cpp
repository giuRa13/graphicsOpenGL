#include <iostream>
#include <SDL2/SDL_image.h>
#include "Texture.hpp"


Texture::Texture()
{
    m_ID = 0;
}


void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_ID); 
}


bool Texture::Load(const std::string& filename)
{
    SDL_Surface* textureData = IMG_Load(filename.c_str());

    if(!textureData)
    {
        std::cout <<"Error loading texture" <<std::endl;
    }

    GLsizei width = textureData->w;
    GLsizei height = textureData->h;
    Uint8* pixels = (Uint8*)textureData->pixels; //pointer to raw data(8 bit at time)
    Uint8 depth = textureData->format->BytesPerPixel; //3 or 4 bite per pixel (rgb or rgba)
    GLint format = ((depth == 4) ? GL_RGBA : GL_RGB);


    glGenTextures(1, &m_ID);
    
    glBindTexture(GL_TEXTURE_2D, m_ID); //bind raw data in openGL texture object
    
        // for Fragment Shader knows how to deal with this image properly(correct textual color chosen in frag shader)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0); 
    
    SDL_FreeSurface(textureData);

    return true;
}


void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0); 
}


void Texture::Unload()
{
    glDeleteTextures(1, &m_ID);
}



