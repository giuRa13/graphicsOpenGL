#include "Quad.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Input.hpp"
#include <glm/ext/matrix_transform.hpp>


Quad::Quad()
{
    GLfloat vertices[] = { [0]=-0.5f,  [1]=0.5f, [2]=0.0f, //t1
                           [3]=0.5f,  [4]=0.5f, [5]=0.0f,
                           [6]=-0.5f, [7]=-0.5f, [8]=0.0f,
                           [9]=-0.5f, [10]=-0.5f, [11]=0.0f, //t2
                           [12]=0.5f,  [13]=0.5f, [14]=0.0f,
                           [15]=0.5f, [16]=-0.5f, [17]=0.0f };
    
    GLfloat colors[] = { [0]=1.0f, [1]=0.0f, [2]=0.0f,
                         [3]=0.0f, [4]=0.0f, [5]=1.0f,
                         [6]=0.0f, [7]=1.0f, [8]=1.0f,
                         [9]=0.0f, [10]=1.1f, [11]=1.1f,
                         [12]=0.0f, [13]=0.0f, [14]=1.0f,
                         [15]=0.0f, [16]=1.0f, [17]=0.f };

    m_buffer.CreateBuffer(6);
    m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
    m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);

    m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
    m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);

    m_position = glm::vec3(0.0f);
    m_rotation = 0.0f;
}


Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}


void Quad::Update()
{
    if(Input::Instance()->IsKeyPressed())
    {
        if(Input::Instance()->GetKeyDown() == 'j')
        {
            m_position.x  -= 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'l')
        {
            m_position.x += 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'i')
        {
            m_position.y += 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'k')
        {
            m_position.y -= 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'u')
        {
            m_position.z += 0.01f;
        }
        else if(Input::Instance()->GetKeyDown() == 'o')
        {
            m_position.z -= 0.01f;
        }


        if(Input::Instance()->GetKeyDown() == 'n')
        {
            m_rotation -= 0.02f; 
        }
        else if(Input::Instance()->GetKeyDown() == 'm')
        {
            m_rotation += 0.02f;
        }
    }
    
    m_model = glm::mat4(1.0f);
   
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    //m_model = glm::translate(m_model, glm::vec3(-0.25f, 0.25f, 0.0f));
    //m_model = glm::rotate(m_model, glm::radians(m_model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    //m_model = glm::scale(m_model, glm::vec3(0.5f, 0.5f, 1.0f));
}


void Quad::Render()
{
    Shader::Instance()->SendUniformData("model", m_model);
    m_buffer.Render(Buffer::TRIANGLES);
}
