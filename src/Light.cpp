#include "Light.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Input.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Light::Light()
{
    m_ambient = glm::vec3(1.0f);
    m_diffuse = glm::vec3(1.0f);
    m_specular = glm::vec3(1.0f);
    m_position = glm::vec3(0.0f, 1.0f, 0.0f);

    GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
    GLfloat colors[] = { 1.0f, 1.0f, 1.0f  };

    m_buffer.CreateBuffer(1);
    m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once); 
    m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), Buffer::FillType::Once);
}

Light::~Light()
{
    m_buffer.DestroyBuffer();
}

void Light::SetSpeed(GLfloat speed)
{
    m_speed = speed;
}


void Light::Update()
{
    if(Input::Instance()->IsKeyPressed())
    {
        if(Input::Instance()->GetKeyDown() == 'j')
        {
            m_position.x  -= m_speed;
        }
        else if(Input::Instance()->GetKeyDown() == 'l')
        {
            m_position.x += m_speed;
        }
        else if(Input::Instance()->GetKeyDown() == 'i')
        {
            m_position.y += m_speed;
        }
        else if(Input::Instance()->GetKeyDown() == 'k')
        {
            m_position.y -= m_speed;
        }
        else if(Input::Instance()->GetKeyDown() == 'u')
        {
            m_position.z -= m_speed;
        }
        else if(Input::Instance()->GetKeyDown() == 'o')
        {
            m_position.z += m_speed;
        }
    }
   
    m_model = glm::mat4( 1.0f);
    m_model = glm::translate( m_model, m_position);
}


void Light::Render(const Shader& shader)
{
    shader.SendUniformData("model", m_model);
    shader.SendUniformData("isLit", false);
    shader.SendUniformData("isTextured", false);

    m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGB, Buffer::DataType::FloatData);

    glPointSize(20.0f);
    m_buffer.Render(Buffer::DrawType::Points);
}


void Light::SendToShader(const Shader& shader)
{
    shader.SendUniformData("light.position", m_position.x, m_position.y, m_position.z);
    shader.SendUniformData("light.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
    shader.SendUniformData("light.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
    shader.SendUniformData("light.specular", m_specular.r, m_specular.g, m_specular.b);
}




