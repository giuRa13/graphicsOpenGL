#include "Screen.hpp"
#include "../include/glad/glad.h"
#include <iostream>


Screen* Screen::Instance()
{
    static Screen* screen = new Screen;
    return screen;
    // the firs call create the object 
    // and the subsequent calls just return that object(pointer to)
}

Screen::Screen()
{
    window = nullptr;
    context = nullptr;
}


bool Screen::Initialize()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout <<"Error initializing SDL" <<std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);


    window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1280, 720, SDL_WINDOW_OPENGL);

    if(window == nullptr)
    {
        std::cout <<"Error initializing SDL window" <<std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);

    if(context == nullptr)
    {
        std::cout <<"Error initializing OpenGL context" <<std::endl;
        return false;
    }

    gladLoadGL();//return 0 or 1
    if(!gladLoadGL())
    {
        std::cout <<"Error Glad loading extensions" <<std::endl;
    }

    return true;
}


void Screen::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


void Screen::Present() //SwapBuffer
{
    SDL_GL_SwapWindow(window);
}


void Screen::Shutdown()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
