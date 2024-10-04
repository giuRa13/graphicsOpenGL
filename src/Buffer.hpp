#pragma once

#include "../include/glad/glad.h"
#include <string>


class Buffer
{

public:
    enum class VBOType { VertexBuffer, ColorBuffer, TextureBuffer };

    enum class ComponentType { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2};

    enum class FillType { Once = GL_STATIC_DRAW, Ongoing = GL_DYNAMIC_DRAW };

    enum class DataType { IntData = GL_INT, FloatData = GL_FLOAT, UnsignedInt = GL_UNSIGNED_INT };

    enum class  DrawType { Points = GL_POINTS, Triangles = GL_TRIANGLES, Lines = GL_LINES };

public:
    Buffer();

    void CreateBuffer(GLuint totalVertices);

    // glBufferData()
    void FillVBO(VBOType vboType,
                 GLfloat* data,
                 GLsizeiptr bufferSize,
                 FillType fillType);
 
    // glVertexAttribPointer()
    void LinkBuffer(const std::string& attribute,
                 VBOType vboType,
                 ComponentType componentType,
                 DataType dataType);

    void Render(DrawType drawType);

    void DestroyBuffer();


private:
    GLuint m_VAO;
    GLuint m_vertexVBO;
    GLuint m_colorVBO;
    GLuint m_textureVBO;
    GLuint m_totalVertices;
};


