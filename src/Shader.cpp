#include <fstream>
#include <iostream>
#include "Shader.hpp"


Shader* Shader::Instance()
{
    static Shader* shaderObject = new Shader();
    return shaderObject;
}

Shader::Shader()
{
    m_shaderProgramID = 0;
    m_vertexShaderID = 0;
    m_fragmentShaderID = 0;
}


bool Shader::CreateProgram()
{
    m_shaderProgramID = glCreateProgram();

    if (m_shaderProgramID == 0)
    {
        std::cout <<"Error creating shader Program" <<std::endl;
        return false;
    }

    return true;
}
      
bool Shader::CreateShaders()
{
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    if(m_vertexShaderID == 0)
    {
        std::cout <<"Error creating Vertex Shader Object" <<std::endl;
        return false;
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    if(m_fragmentShaderID == 0)
    {
        std::cout <<"Error creating Fragmen Shader Object" <<std::endl;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////
bool Shader::CompileShaders(const std::string& filename, ShaderType shaderType)
{
    std::fstream file;
    std::string text;
    std::string sourceCode;
    GLuint shaderID;

    shaderID = (shaderType == ShaderType::VERTEX_SHADER) ? m_vertexShaderID : m_fragmentShaderID;

    file.open(filename);

    if(!file)
    {
        std::cout <<"Error reading shader file: " <<filename  <<std::endl;
        return false;
    }

    while(!file.eof()) 
    {
        std::getline(file, text);
        sourceCode += text + "\n";
    }
    file.close();

    const GLchar* finalSourceCode = reinterpret_cast<const GLchar*>(sourceCode.c_str());
    glShaderSource(shaderID, 1, &finalSourceCode, nullptr);

    glCompileShader(shaderID);
    
    GLint errorCode;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &errorCode);
    
    if(errorCode == GL_TRUE)
    {
        std::cout <<"Shader Compilation Successfull" <<std::endl;
    }
    else
    {
        GLchar errorMessage[1000];
        GLsizei bufferSize = 1000;

        glGetShaderInfoLog(shaderID, bufferSize, &bufferSize, errorMessage);
        std::cout <<errorMessage <<std::endl;
    }
    
    return true;
}
////////////////////////////////////////////////////////////////////////////////////


void Shader::AttachShaders()
{
    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}


bool Shader::LinkProgram()
{
    glLinkProgram(m_shaderProgramID);

    glUseProgram(m_shaderProgramID);

    GLint errorCode;
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS,  &errorCode);
    
    if(errorCode == GL_TRUE)
    {
        std::cout <<"Shader Linking Successfull" <<std::endl;
    }
    else
    {
        GLchar errorMessage[1000];
        GLsizei bufferSize = 1000;
 
        glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);
        std::cout <<errorMessage <<std::endl;
    }

    return true;
}


 void Shader::DetachShaders() //NOT KILL off the shaders or program
{
    glDetachShader(m_shaderProgramID, m_vertexShaderID);
    glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
    glDeleteProgram(m_shaderProgramID);
}

