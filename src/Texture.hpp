#pragma once

#include "../include/glad/glad.h"
#include <string>


class Texture
{

public:
    Texture();

    void Bind() const;
    bool Load(const std::string& filename);
    void Unbind();
    void Unload();


private:
    GLuint m_ID;

};



