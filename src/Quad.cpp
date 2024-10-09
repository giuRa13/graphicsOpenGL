#include "Quad.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
//#include "Input.hpp"
#include "Material.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>


Quad::Quad(const std::string& textureFilename)
{
    /*GLfloat vertices[] = { [0]=-0.5f,  [1]=0.5f, [2]=0.0f, //t1
                           [3]=0.5f,  [4]=0.5f, [5]=0.0f,
                           [6]=-0.5f, [7]=-0.5f, [8]=0.0f,
                           [9]=-0.5f, [10]=-0.5f, [11]=0.0f, //t2
                           [12]=0.5f,  [13]=0.5f, [14]=0.0f,
                           [15]=0.5f, [16]=-0.5f, [17]=0.0f };*/
    GLfloat vertices[] = { -0.5f,  0.5f, 0.0f, //t1
                           0.5f,  0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f };


   /*GLfloat colors[] = { [0]=1.0f, [1]=0.0f, [2]=0.0f,
                         [3]=0.0f, [4]=0.0f, [5]=1.0f,
                         [6]=0.0f, [7]=1.0f, [8]=1.0f,
                         [9]=0.0f, [10]=1.1f, [11]=1.1f,
                         [12]=0.0f, [13]=0.0f, [14]=1.0f,
                         [15]=0.0f, [16]=1.0f, [17]=0.f };*/
   GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f };
   /*GLfloat colors[] = { [0]=1.0f, [1]=1.0f, [2]=1.0f,
                         [3]=1.0f, [4]=1.0f, [5]=1.0f,
                         [6]=1.0f, [7]=1.0f, [8]=1.0f,
                         [9]=1.0f, [10]=1.1f, [11]=1.1f,
                         [12]=1.0f, [13]=1.0f, [14]=1.0f,
                         [15]=1.0f, [16]=1.0f, [17]=1.0f };*/

    GLfloat normals[] = { 0.0f, 0.0f, 1.0f,
                          0.0f ,0.0f, 1.0f,
                          0.0f, 0.0f, 1.0f,
                          0.0f, 0.0f, 1.0f  };

    /*GLfloat UVs[] = { 0.0f, 1.0f,
                      1.0f, 1.0f,
                      0.0f, 0.0f,
                      0.0f, 0.0f,
                      1.0f, 1.0f,
                      1.0f, 0.0f};*/
    GLfloat UVs[] = { 0.0f, 1.0f,
                      1.0f, 1.0f,
                      1.0f, 0.0f,
                      0.0f, 0.0f};

    GLuint indices[] = { 0, 1, 3,
                          3, 1, 2 };


    m_buffer.CreateBuffer(6, true); //true hasEBO
    
    m_buffer.FillEBO(indices, sizeof(indices), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::TextureBuffer, UVs, sizeof(UVs), Buffer::FillType::Once);
    m_buffer.FillVBO(Buffer::VBOType::NormalBuffer, normals, sizeof(normals), Buffer::FillType::Once);

    m_buffer.LinkEBO();

    m_texture.Load( "textures/" + textureFilename);
    
    m_position = glm::vec3(0.0f);
    m_rotation = glm::vec3(0.0f); 
    m_scale = glm::vec3(1.0f); 

    m_material.SetShininess(50.0f);
    m_material.SetAmbient(glm::vec3(0.4f, 0.4f, 0.4f));
    m_material.SetDiffuse(glm::vec3(0.1f, 0.7f, 0.2f));
    m_material.SetSpecular(glm::vec3(0.8f, 0.8f, 0.8f));
}

Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}

void Quad::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}

void Quad::SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll)
{
    m_rotation.x = pitch;
    m_rotation.y = yaw;
    m_rotation.z = roll;
}

void Quad::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}


void Quad::Render(const Shader &shader)
{

    m_model = glm::mat4(1.0f);   
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));//rotate 90 on the X axis
    m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));//rotate 90 on the X axis
    m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));//rotate 90 on the X axis
    m_model = glm::scale(m_model, m_scale);
    m_normal = glm::inverse(glm::mat3(m_model));
    
    shader.SendUniformData("model", m_model);
    shader.SendUniformData("normal", m_normal);
    shader.SendUniformData("isTextured", true);

    m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader, "textureIn", Buffer::VBOType::TextureBuffer, Buffer::ComponentType::UV, Buffer::DataType::FloatData);
    m_buffer.LinkVBO(shader, "normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);

    m_texture.Bind();
    m_buffer.Render(Buffer::DrawType::Triangles);
    m_texture.Unbind();
}



