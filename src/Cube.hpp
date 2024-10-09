#pragma once


#include "../include/glad/glad.h"
#include <glm/glm.hpp>
#include "Buffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Material.hpp"


class Cube
{

public:
    Cube(const std::string& textureFilename);
    ~Cube();

    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll);
    void SetScale(GLfloat x, GLfloat y, GLfloat z);

    void Update() {};
    void Render(const Shader& shader);


private:
    Buffer m_buffer;
    Texture m_texture;
    Material m_material;

    glm::mat4 m_model;
    glm::mat3 m_normal;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

};



