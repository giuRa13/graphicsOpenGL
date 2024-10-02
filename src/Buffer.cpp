#include "Buffer.hpp"
#include "Shader.hpp"


Buffer::Buffer()
{
    m_VAO = 0;
    m_vertexVBO = 0;
    m_colorVBO = 0;
    m_totalVertices = 0;
}


void Buffer::CreateBuffer(GLuint totalVertices)
{
    // generate Buffers(in memory)
    glGenBuffers(1, &m_vertexVBO);
    glGenBuffers(1, &m_colorVBO);
    glGenVertexArrays(1, &m_VAO);
    m_totalVertices = totalVertices;
}


void Buffer::FillVBO(VBOType vboType, GLfloat *data, GLsizeiptr bufferSize, FillType fillType)
{
    glBindVertexArray(m_VAO); //bind the 2 VBOs in VAO
   
        if(vboType == VERTEX_BUFFER)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        }

        glBufferData(GL_ARRAY_BUFFER, bufferSize, data, fillType); //take raw data(array) and put in VBO
    
    glBindVertexArray(0);
}


void Buffer::LinkBuffer(const std::string& attribute, VBOType vboType,
                        ComponentType componentType, DataType dataType)
{
    GLuint shaderProgramID = Shader::Instance()->GetShaderProgramID();
    
    GLint ID = glGetAttribLocation(shaderProgramID, attribute.c_str()); //attribute="vertexIn", "colorIn"
   
    glBindVertexArray(m_VAO);
    
        if(vboType == VERTEX_BUFFER)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
        }

        // link VBO with the vertex Attribute so the shaders know whats coming in
        glVertexAttribPointer(ID, componentType, GL_FLOAT, GL_FALSE, 0, nullptr); //normalized=false //nullptr=start at the begin
        glEnableVertexAttribArray(ID);

    glBindVertexArray(0);
}


void Buffer::Render(DrawType drawType)
{
    glBindVertexArray(m_VAO); 
    glDrawArrays(drawType, 0, m_totalVertices); //0=start 
    glBindVertexArray(0);

}

void Buffer::DestroyBuffer()
{
    glDeleteBuffers(1, &m_vertexVBO);
    glDeleteBuffers(1, &m_colorVBO);
    glDeleteVertexArrays(1, &m_VAO);
}


