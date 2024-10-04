#include "Cube.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>


Cube::Cube()
{
    GLfloat vertices[] = { -0.5f,  0.5f,  0.5f,   //front
                            0.5f,  0.5f,  0.5f,
                            0.5f, -0.5f,  0.5f,
                           -0.5f, -0.5f,  0.5f,

                            0.5f,  0.5f, -0.5f,   //back
                           -0.5f,  0.5f, -0.5f,
                           -0.5f, -0.5f, -0.5f,
                            0.5f, -0.5f, -0.5f,

                            -0.5f,  0.5f, -0.5f,   //left
                           -0.5f,  0.5f, 0.5f,
                           -0.5f, -0.5f, 0.5f,
                            -0.5f, -0.5f, -0.5f,

                            0.5f,  0.5f, 0.5f,   //right
                           0.5f,  0.5f, -0.5f,
                           0.5f, -0.5f, -0.5f,
                            0.5f, -0.5f, 0.5f,

                            -0.5f,  0.5f, -0.5f,   //top
                           0.5f,  0.5f, -0.5f,
                           0.5f, 0.5f, 0.5f,
                            -0.5f, 0.5f, 0.5f,

                            -0.5f,  -0.5f, 0.5f,   //bottom
                           0.5f,  -0.5f, 0.5f,
                           0.5f, -0.5f, -0.5f,
                            -0.5f, -0.5f, -0.5f };


    GLfloat colors[] = { 1.0f, 0.0f, 0.0f,   //front
                         1.0f, 0.0f, 0.0f,
                         1.0f, 0.0f, 0.0f,
                         1.0f, 0.0f, 0.0f,

                         0.0f, 1.0f, 0.0f,   //back
                         0.0f, 1.0f, 0.0f,
                         0.0f, 1.0f, 0.0f,
                         0.0f, 1.0f, 0.0f,

                         0.0f, 0.0f, 1.0f,   //left
                         0.0f, 0.0f, 1.0f,
                         0.0f, 0.0f, 1.0f,
                         0.0f, 0.0f, 1.0f,

                         1.0f, 1.0f, 0.0f,  //right
                         1.0f, 1.0f, 0.0f,
                         1.0f, 1.0f, 0.0f,
                         1.0f, 1.0f, 0.0f,

                         1.0f, 0.0f, 1.0f,   //top
                         1.0f, 0.0f, 1.0f,
                         1.0f, 0.0f, 1.0f,
                         1.0f, 0.0f, 1.0f,

                         0.0f, 1.0f, 1.0f,   //bottom
                         0.0f, 1.0f, 1.0f,
                         0.0f, 1.0f, 1.0f,
                         0.0f, 1.0f, 1.0f  };

    GLuint indices[] = {  0,  1,  3,  3,  1,  2,  
                          4,  5,  7,  7,  5,  6,
                          8,  9, 11, 11,  9, 10,
                         12, 13, 15, 15, 13, 14,
                         16, 17, 19, 19, 17, 18, 
                         20, 21, 23, 23, 21, 22  };

    m_buffer.CreateBuffer(36, true);
    m_buffer.FillEBO(indices,  sizeof(indices), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once);    
    m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), Buffer::FillType::Once);
    
    m_buffer.LinkEBO();
    m_buffer.LinkVBO("vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
    m_buffer.LinkVBO("colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGB, Buffer::DataType::FloatData);

    m_position = glm::vec3(0.0f);
}


Cube::~Cube()
{
    m_buffer.DestroyBuffer();
}


void Cube::Update()
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_position);
}


void Cube::Render()
{
    Shader::Instance()->SendUniformData("model", m_model);
    Shader::Instance()->SendUniformData("isLit", false);
    Shader::Instance()->SendUniformData("isTextured", false);
    m_buffer.Render(Buffer::DrawType::Triangles);
}




