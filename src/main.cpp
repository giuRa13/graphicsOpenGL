//g++ main.cpp -o main.o -lSDL2 -lGL 
//g++ ./src/*.cpp ./src/glad.c -I./src/*.hpp -I./include -o main.exe -lSDL2 
//g++ ./src/*.cpp ./src/glad.c -I./src/*.hpp -I./include -o main.exe -lSDL2 -lSDL2_image
#include <iostream>
#include <SDL2/SDL.h>
#include "../include/glad/glad.h"
#include <glm/glm.hpp>
#include "Screen.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include "Quad.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Cube.hpp"


void GetOpenGLVersionInfo()
{
    std::cout <<"Vendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
    std::cout <<"\n";
}



bool isRunning = true;


int main(int argc, char* argv[])
{

    Screen::Instance()->Initialize();

    GetOpenGLVersionInfo();

    Shader lightShader;
    lightShader.Create("shaders/main.vert", "shaders/main.frag");
    lightShader.Use();

    float xPos = 0.0f;
    float yPos = 0.0f;

    /////////////////////////////////////////////////////////
    Quad quad;
    Cube cube;
    Camera camera;
    
    camera.Set3DView();

    Light light;
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
        camera.SendToShader(lightShader);

        light.Update();
        light.Render(lightShader);
        light.SendToShader(lightShader);

        //quad.Update();
        //quad.Render();
        cube.Update();
        cube.Render(lightShader);
    

        Screen::Instance()->Present();    
        //////////////////////////////////////////////////////
    }


    lightShader.Destroy();

    Screen::Instance()->Shutdown();

    return 0;
}



