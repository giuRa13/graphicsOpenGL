//g++ main.cpp -o main.o -lSDL2 -lGL 

#include <GL/gl.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.hpp"
#include "Input.hpp"


bool isRunning = true;


int main(int argc, char* argv[])
{

    Screen::Instance()->Initialize();

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

    Screen::Instance()->Shutdown();

    return 0;
}
