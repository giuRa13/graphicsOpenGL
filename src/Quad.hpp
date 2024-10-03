#pragma once

#include "../include/glad/glad.h"
#include "Buffer.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class Quad
{

public:
    Quad();
    ~Quad();

    void Update();
    void Render();


private:
    Buffer m_buffer;
    Texture m_texture;

    glm::mat4 m_model;
    glm::vec3 m_position;
    GLfloat m_rotation;
};


