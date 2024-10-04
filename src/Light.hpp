#pragma once


#include <glm/glm.hpp>
#include "Buffer.hpp"



class Light
{

public:
    Light();
    ~Light();

    void Update();
    void Render();
    void SendToShader();


private:
    Buffer m_buffer;

    glm::mat4 m_model;
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

};



