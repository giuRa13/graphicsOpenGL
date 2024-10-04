#include "Quad.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"
//#include "Input.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>


Quad::Quad()
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
   GLfloat colors[] = { 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f,
                         0.0f, 1.0f, 0.0f,
                         0.0f, 1.0f, 1.0f };
   /*GLfloat colors[] = { [0]=1.0f, [1]=1.0f, [2]=1.0f,
                         [3]=1.0f, [4]=1.0f, [5]=1.0f,
                         [6]=1.0f, [7]=1.0f, [8]=1.0f,
                         [9]=1.0f, [10]=1.1f, [11]=1.1f,
                         [12]=1.0f, [13]=1.0f, [14]=1.0f,
                         [15]=1.0f, [16]=1.0f, [17]=1.0f };*/

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

    m_buffer.LinkEBO();
    m_buffer.LinkVBO("vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
    m_buffer.LinkVBO("colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGB, Buffer::DataType::FloatData);
    m_buffer.LinkVBO("textureIn", Buffer::VBOType::TextureBuffer, Buffer::ComponentType::UV, Buffer::DataType::FloatData);

    m_texture.Load( "textures/wood1.png");
    
    m_shininess = 60.0f;
    m_position = glm::vec3(0.0f);
    m_ambient = glm::vec3(0.4f, 0.4f, 0.4f); //shade of gray
    m_diffuse = glm::vec3(0.1f, 0.8f, 0.2f); //more green
    m_specular = glm::vec3(0.8f, 0.8f, 0.8f); //almost white
}


Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}


void Quad::Update()
{
    /*if(Input::Instance()->IsKeyPressed())
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
    }*/
    
    m_model = glm::mat4(1.0f);
   
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));//rotate 90 on the X axis
    //m_model = glm::translate(m_model, glm::vec3(-0.25f, 0.25f, 0.0f));
    //m_model = glm::rotate(m_model, glm::radians(m_model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    //m_model = glm::scale(m_model, glm::vec3(0.5f, 0.5f, 1.0f));
}


void Quad::Render()
{
    Shader::Instance()->SendUniformData("model", m_model);
    Shader::Instance()->SendUniformData("isLit", false);
    Shader::Instance()->SendUniformData("isTextured", false);

    Shader::Instance()->SendUniformData("material.shininess", m_shininess);
    Shader::Instance()->SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
    Shader::Instance()->SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
    Shader::Instance()->SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);

    m_texture.Bind();
    m_buffer.Render(Buffer::DrawType::Triangles);
    m_texture.Unbind();
}



