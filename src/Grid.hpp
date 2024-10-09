#pragma once


#include "../include/glad/glad.h"
#include <glm/glm.hpp>
#include "Buffer.hpp"
#include "Shader.hpp"



class Grid
{

public:
    Grid();

    void Update() {};
    void Render(const Shader& shader);


private:
    Buffer m_buffer;

    glm::mat4 m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation;

};



