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
#include "Model.hpp"
#include "Grid.hpp"



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

    Shader defaultShader;
    defaultShader.Create("shaders/default.vert", "shaders/default.frag");
    
    Shader lightShader;
    lightShader.Create("shaders/light.vert", "shaders/light.frag");

    float xPos = 0.0f;
    float yPos = 0.0f;

    /////////////////////////////////////////////////////////
    
    Quad floor("Floor.jpg");
    floor.SetRotation(90.0f, 0.0f, 0.0f);
    floor.SetScale(25.0f, 25.0f, 1.0f);//(double of grid SIZE)
    
    Cube cube1("wood1.png");
    cube1.SetPosition(-1.0f, 0.25f, -2.0f);
    cube1.SetRotation(0.0f, 45.0f, 0.0f);
    cube1.SetScale(0.5f, 0.5f, 0.5f);

    Cube cube2("wood2.png");
    cube2.SetPosition(-0.5f, 0.25f, -3.0f);
    cube2.SetRotation(0.0f, 80.0f, 0.0f);
    cube2.SetScale(0.5f, 0.5f, 0.5f);

    Model cabinet;
    cabinet.Load("models/Armchair.obj");
    cabinet.SetPosition(3.0f, 0.25f, -3.0f);
    cabinet.SetRotation(0.0f, 135.0f, 0.0f);

    Grid grid;

    Camera camera;
    camera.Set3DView();
    camera.SetSpeed(0.1f);


    //Model model;
    //model.Load("models/Cabinet.obj");
    
    Light light;
    light.SetSpeed(0.1f);
    ////////////////////////////////////////////////////////


    while(isRunning)
    {
        Screen::Instance()->ClearScreen();
        
        Input::Instance()->Update();
        
        char keyPressed = Input::Instance()->GetKeyDown();

        isRunning = !Input::Instance()->IsXClicked();

        /*if(Input::Instance()->IsLeftButtonClicked())
        {
            m_rotation.x += Input::Instance()->GetMouseMotionY();
             m_rotation.y += Input::Instance()->GetMouseMotionX();
        }*/

        /*if(Input::Instance()->IsLeftButtonClicked())
        {
            std::cout <<"Left mouse button clicked" <<std::endl;
        }*/

        /*int mouseX = Input::Instance()->GetMousePositionX();
        int mouseY = Input::Instance()->GetMousePositionY();
        std::cout <<"Mouse position: " <<mouseX <<", " <<mouseY <<std::endl;*/


        // update/render /////////////////////////////////////
        camera.Update();
        light.Update();

        //quad.Update();
        //quad.Render();
       
        defaultShader.Use();
        camera.SendToShader(defaultShader);
      
        grid.Render(defaultShader);
        cube1.Render(defaultShader);


        lightShader.Use();
        light.SendToShader(lightShader);
        camera.SendToShader(lightShader);
        
        light.Render(lightShader);
        floor.Render(lightShader);
        cube2.Render(lightShader);
        cabinet.Render(lightShader);

        Screen::Instance()->Present();    
        //////////////////////////////////////////////////////
    }


    lightShader.Destroy();

    Screen::Instance()->Shutdown();

    return 0;
}



