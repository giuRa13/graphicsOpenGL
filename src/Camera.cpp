#include "Camera.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
{
    m_view = glm::mat4(1.0f);
    m_proj = glm::mat4(1.0f);

    m_position = glm::vec3(0.0f);
    m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}


void Camera::Set3DView()
{
    GLfloat FOV = 45.0f;
    GLfloat aspectRatio = 1280.0f / 720.0f;

    m_proj = glm::perspective(FOV, aspectRatio, 0.001f, 1000.0f); //front wall, back wall
    Shader::Instance()->SendUniformData("proj", m_proj);
}


void Camera::Update()
{
    if(Input::Instance()->IsKeyPressed())
    {
        if(Input::Instance()->GetKeyDown() == 'a')
        {
            m_position.x  -= 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'd')
        {
            m_position.x += 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'w')
        {
            m_position.y += 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 's')
        {
            m_position.y -= 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'q')
        {
            m_position.z += 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'e')
        {
            m_position.z -= 0.01f;
        }

    }

    m_view = glm::lookAt(m_position, m_position + m_direction, m_up); //position, target, worldUp
    Shader::Instance()->SendUniformData("view", m_view);
}

