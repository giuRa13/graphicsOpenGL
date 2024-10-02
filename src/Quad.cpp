#include "Quad.hpp"
#include "Buffer.hpp"


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
}


Quad::~Quad()
{
    m_buffer.DestroyBuffer();
}


void Quad::Render()
{
    m_buffer.Render(Buffer::TRIANGLES);
}
