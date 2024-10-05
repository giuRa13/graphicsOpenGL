#pragma once


#include <glm/glm.hpp>
#include "Buffer.hpp"



class Cube
{

public:
    Cube();
    ~Cube();

    void Update();
    void Render();


private:
    Buffer m_buffer;

    glm::mat4 m_model;
    glm::vec3 m_position;

    float m_shininess;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
};



