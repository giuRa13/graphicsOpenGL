#include "Cube.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
#include "Input.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>


Cube::Cube(const std::string& textureFilename)
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


    GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,   //front
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,

                         1.0f, 1.0f, 1.0f, 1.0f,   //back
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,

                         1.0f, 1.0f, 1.0f, 1.0f,   //left
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,

                         1.0f, 1.0f, 1.0f, 1.0f,  //right
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,

                         1.0f, 1.0f, 1.0f, 1.0f,   //top
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,

                         1.0f, 1.0f, 1.0f, 1.0f,   //bottom
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f  };

    
    GLfloat UVs[] = { 0.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 0.0f,

                      0.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 0.0f, 
   
                      0.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 0.0f, 

                      0.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 0.0f, 
    
                      0.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 0.0f, 

                      0.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 0.0f  };

    
    GLfloat normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 

                          0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
                          0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 

                          -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                          -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 

                          1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                          1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 

                          0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 

                          0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
                          0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f  };


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
    m_buffer.FillVBO(Buffer::VBOType::TextureBuffer, UVs, sizeof(UVs), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::NormalBuffer, normals, sizeof(normals), Buffer::FillType::Once);

    m_buffer.LinkEBO();

    m_texture.Load(/*"../textures/"  +*/  textureFilename);

    m_position = glm::vec3(0.0f);
    m_rotation = glm::vec3(0.0f);
    m_scale = glm::vec3(1.0f);
    
    m_material.SetShininess(50.0f);
    m_material.SetAmbient(glm::vec3(0.4f, 0.4f, 0.4f)); //shade of gray
    m_material.SetDiffuse(glm::vec3(0.1f, 0.7f, 0.2f)); //more green
    m_material.SetSpecular(glm::vec3(0.8f, 0.8f, 0.8f)); //almost white

}


Cube::~Cube()
{
    m_buffer.DestroyBuffer();
}


void Cube::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}

void Cube::SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll)
{
    m_rotation.x = pitch;
    m_rotation.y = yaw;
    m_rotation.z = roll;
}

void Cube::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}


void Cube::Render(const Shader& shader)
{

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::scale(m_model, m_scale);
    m_normal = glm::inverse(glm::mat3(m_model));
    
    shader.SendUniformData("model", m_model);
    shader.SendUniformData("normal", m_normal);
    shader.SendUniformData("isTextured", true);

    m_material.SendToShader(shader);

    m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader,"textureIn", Buffer::VBOType::TextureBuffer, Buffer::ComponentType::UV, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader, "normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
    
    m_texture.Bind();
    m_buffer.Render(Buffer::DrawType::Triangles);
    m_texture.Unbind();
}




