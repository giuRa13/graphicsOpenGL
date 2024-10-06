#pragma once


#include <glm/glm.hpp>
#include "../include/glad/glad.h"
#include "Shader.hpp"


class Camera
{

public:
    Camera();

    void Set3DView();
    void Update();
    void SendToShader(const Shader& shader);


protected:
    glm::mat4 m_view;
    glm::mat4 m_proj;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;

};



