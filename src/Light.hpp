#pragma once


#include "../include/glad/glad.h"
#include <glm/glm.hpp>
#include "Buffer.hpp"
#include "Shader.hpp"


class Light
{

public:
    Light();
    ~Light();

    void SetSpeed(GLfloat speed);

    void Update();
    void Render(const Shader& shader);
    void SendToShader(const Shader& shader);


private:
    Buffer m_buffer;
    GLfloat m_speed;

    glm::mat4 m_model;
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

};



