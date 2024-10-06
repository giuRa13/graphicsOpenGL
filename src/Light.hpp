#pragma once


#include <glm/glm.hpp>
#include "Buffer.hpp"
#include "Shader.hpp"


class Light
{

public:
    Light();
    ~Light();

    void Update();
    void Render(const Shader& shader);
    void SendToShader(const Shader& shader);


private:
    Buffer m_buffer;

    glm::mat4 m_model;
    glm::vec3 m_position;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

};



