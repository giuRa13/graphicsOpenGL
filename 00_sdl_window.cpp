// g++ main.cpp ./src/glad.c -I./include -o 00_sdl_window.o -lSDL2 

#include <SDL2/SDL.h>
#include "include/glad/glad.h"
#include <iostream>


int gScreenWidth = 640;
int gScreenHeight = 480;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit = false; //if true we quit


void GetOpenGLVersionInfo(){
    std::cout <<"Vendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
}

void InitializeProgram()
{
    if(SDL_INIT_VIDEO < 0){
        std::cout <<"SDL2 could not initialize video subsystem" <<std::endl;
        exit(1);
    }

    gGraphicsApplicationWindow =  SDL_CreateWindow("OpenGL Window",
            0, 0, 
            gScreenWidth, gScreenHeight,
            SDL_WINDOW_OPENGL);
   
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //updating(twice as often)
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //color 24bit

    if(gGraphicsApplicationWindow == nullptr){
        std::cout <<"Error creating SDL_Window" <<std::endl;
        exit(1);    
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if(gOpenGLContext == nullptr){
        std::cout <<"Error initializing OpenGL Context" <<SDL_GetError() <<std::endl;
        exit(1);
    }

    //init glad
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout <<"glad not initialize" <<std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void Input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0){
        if(event.type == SDL_QUIT){
            std::cout <<"Goodbye!" <<std::endl;
            gQuit = true;
        }
    }
}

void Draw()
{

}

void PreDraw()
{

}

void MainLoop()
{
    while(!gQuit){
        Input();
        PreDraw();
        Draw();

        SDL_GL_SwapWindow(gGraphicsApplicationWindow); //update the screen
    }
}

void CleanUp()
{
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}


int main()
{
    InitializeProgram();
    
    MainLoop();
    
    CleanUp();

    return 0;
}

