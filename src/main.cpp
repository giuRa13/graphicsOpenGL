//g++ main.cpp -o main.o -lSDL2 -lGL 
//g++ ./src/*.cpp ./src/glad.c -I./src/*.hpp -I./include -o main.exe -lSDL2 

#include <iostream>
#include <SDL2/SDL.h>
#include "../include/glad/glad.h"
#include "Screen.hpp"
#include "Input.hpp"
#include "Shader.hpp"


bool isRunning = true;


int main(int argc, char* argv[])
{

    Screen::Instance()->Initialize();

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


        //update/render
        glBegin(GL_QUADS);
            glColor3f(1,0,0);
            glVertex3f(xPos- 0.5f, yPos + 0.5f, 0.0f);
            
            glColor3f(0,1,0);
            glVertex3f(xPos + 0.5f, yPos + 0.5f, 0.0f);

            glColor3f(0,0,1);
            glVertex3f(xPos +0.5f,  yPos -0.5f,  0.0f);

            glColor3f(0,0,1);
            glVertex3f(xPos - 0.5, yPos - 0.5f, 0.0f);
        glEnd();

        Screen::Instance()->Present();
    
    }

    Shader::Instance()->DetachShaders();
    Shader::Instance()->DestroyShaders();
    Shader::Instance()->DestroyProgram();

    Screen::Instance()->Shutdown();

    return 0;
}
