//g++ main.cpp -o main.o -lSDL2 -lGL 

#include <GL/gl.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.hpp"



bool isRunning = true;


int main(int argc, char* argv[])
{

    Screen::Instance()->Initialize();

    while(isRunning)
    {

        Screen::Instance()->ClearScreen();

        //update/render
        glBegin(GL_QUADS);
            glColor3f(1,0,0);
            glVertex3f(-0.5f, 0.5f, 0.0f);
            
            glColor3f(0,1,0);
            glVertex3f(0.5f, 0.5f, 0.0f);

            glColor3f(0,0,1);
            glVertex3f(0.5f,  -0.5f,  0.0f);

            glColor3f(0,0,1);
            glVertex3f(-0.5, -0.5f, 0.0f);
        glEnd();

        Screen::Instance()->Present();
    
    }

    Screen::Instance()->Shutdown();

    system("pause");
    return 0;
}
