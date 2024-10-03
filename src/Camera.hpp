#pragma once


#include <glm/glm.hpp>
#include "../include/glad/glad.h"


class Camera
{

public:
    Camera();

    void Update();


protected:
    glm::mat4 m_view;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;

};



