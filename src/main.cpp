//g++ main.cpp -o main.o -lSDL2 -lGL 
//g++ ./src/*.cpp ./src/glad.c -I./src/*.hpp -I./include -o main.exe -lSDL2 

#include <iostream>
#include <SDL2/SDL.h>
#include "../include/glad/glad.h"
#include <glm/glm.hpp>
#include "Screen.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include "Quad.hpp"
#include "Camera.hpp"



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


    /////////////////////////////////////////////////////////
    
    Quad quad;
    Camera camera;
    
    camera.Set3DView();

    ////////////////////////////////////////////////////////


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


        // update/render /////////////////////////////////////
        camera.Update();

        quad.Update();
        quad.Render();
        
        //////////////////////////////////////////////////////
        

        Screen::Instance()->Present();    
    }

    Shader::Instance()->DetachShaders();
    Shader::Instance()->DestroyShaders();
    Shader::Instance()->DestroyProgram();

    Screen::Instance()->Shutdown();

    return 0;
}
