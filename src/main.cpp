//g++ main.cpp -o main.o -lSDL2 -lGL 
//g++ ./src/*.cpp ./src/glad.c -I./src/*.hpp -I./include -o main.exe -lSDL2 

#include <iostream>
#include <SDL2/SDL.h>
#include "../include/glad/glad.h"
#include "Screen.hpp"
#include "Input.hpp"
#include "Shader.hpp"


bool isRunning = true;

void GetOpenGLVersionInfo()
{
    std::cout <<"Vendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
    std::cout <<"\n";
}


int main(int argc, char* argv[])
{

    Screen::Instance()->Initialize();

    GetOpenGLVersionInfo();

    if(!Shader::Instance()->CreateProgram()) return 0;
    if(!Shader::Instance()->CreateShaders()) return 0;
    if(!Shader::Instance()->CompileShaders("shaders/main.vert", Shader::ShaderType::VERTEX_SHADER)) 
    { 
        //... 
    };
    if(!Shader::Instance()->CompileShaders("shaders/main.frag", Shader::ShaderType::FRAGMENT_SHADER))
    {
        //...
    };

    Shader::Instance()->AttachShaders();
    
    if(!Shader::Instance()->LinkProgram())
    {
        //...
    };

    float xPos = 0.0f;
    float yPos = 0.0f;


    GLfloat vertices[] = { -0.5f,  0.5f, 0.0f, //t1
                            0.5f,  0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f, //t2
                            0.5f,  0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };

    GLfloat colors[] = { 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f,
                         0.0f, 1.0f, 1.0f,
                         0.0f, 1.1f, 1.1f,
                         0.0f, 0.0f, 1.0f,
                         0.0f, 1.0f, 0.f };
    // variables in Shaders
    GLuint shaderProgramID = Shader::Instance()->GetShaderProgramID();
    GLint vertexID = glGetAttribLocation(shaderProgramID, "vertexIn");
    GLint colorID = glGetAttribLocation(shaderProgramID, "colorIn");
    // create VBO
    GLuint vertexVBO;
    GLuint colorVBO;
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &colorVBO);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); //bind the 2 VBOs toghether

        // pass Data to VBO
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link VBO with the vertex Attribute so the shaders know whats coming in 
        glVertexAttribPointer(vertexID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); //normalized=false //nullptr=start at the begin
        glEnableVertexAttribArray(vertexID);

        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);  
        glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 0, nullptr); 
        glEnableVertexAttribArray(colorID);
    
    glBindVertexArray(0);



    while(isRunning)
    {

        Screen::Instance()->ClearScreen();
        
        Input::Instance()->Update();
        
        char keyPressed = Input::Instance()->GetKeyDown();

        if(Input::Instance()->IsXClicked())
        {
            isRunning = false;
        }
        
        /*if(Input::Instance()->IsLeftButtonClicked())
        {
            std::cout <<"Left mouse button clicked" <<std::endl;
        }*/

        /*int mouseX = Input::Instance()->GetMousePositionX();
        int mouseY = Input::Instance()->GetMousePositionY();
        std::cout <<"Mouse position: " <<mouseX <<", " <<mouseY <<std::endl;*/
        if(Input::Instance()->IsKeyPressed())
        {
            if(Input::Instance()->GetKeyDown() == 'a')
            {
                xPos -= 0.01f;
            }
            else if(Input::Instance()->GetKeyDown() == 'd')
            {
                xPos += 0.01f;
            }
            else if(Input::Instance()->GetKeyDown() == 'w')
            {
                yPos += 0.01f;
            }
            else if(Input::Instance()->GetKeyDown() == 's')
            {
                yPos -= 0.01f;
            }
        }


        // update/render /////////////////////////////////////
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); //0=start 
        glBindVertexArray(0);

        Screen::Instance()->Present();
    
    }

    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &colorVBO);
    glDeleteVertexArrays(1, &VAO);
    
    glDisableVertexAttribArray(vertexID);
    glDisableVertexAttribArray(colorID);

    Shader::Instance()->DetachShaders();
    Shader::Instance()->DestroyShaders();
    Shader::Instance()->DestroyProgram();

    Screen::Instance()->Shutdown();

    return 0;
}
