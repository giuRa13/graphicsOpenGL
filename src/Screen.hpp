#pragma once

#include <SDL2/SDL.h>


class Screen
{
public: //wherever include Screen.h I have an instant access to the Instance func
    static Screen* Instance(); //(When call "Instance" it returns this pointer pointing to this Screen Manager)
                               // (only whit this func can have access to this)
public:
    bool Initialize();
    void ClearScreen();
    void Present(); //SwapBuffer
    void Shutdown();


private: //private constructor so nobody can create a Screen by himself but can use this(singleton)
    Screen();
    Screen(const Screen&); // copy constuctor same(can't duplicate)
    Screen& operator=(const Screen&); //can not assign one Screen to another


private:
    SDL_Window* window;
    SDL_GLContext context;
};
