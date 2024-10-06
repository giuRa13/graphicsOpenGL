#pragma once


#include <glm/glm.hpp>
#include "Buffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"


class Cube
{

public:
    Cube();
    ~Cube();

    void Update();
    void Render(const Shader& shader);


private:
    Buffer m_buffer;
    Texture m_texture;

    glm::mat4 m_model;
    glm::mat3 m_normal;

    glm::vec3 m_position;
    glm::vec3 m_rotation;

    float m_shininess;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
};



