// g++ main.cpp ./src/glad.c -I./include -o 00_sdl_window.o -lSDL2 

#include <SDL2/SDL.h>
#include "include/glad/glad.h"
#include <iostream>
#include <string>
#include <vector>


int gScreenWidth = 640;
int gScreenHeight = 480;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false; //if true we quit

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;

GLuint gGraphicsPipelineShadersProgram = 0;

const std::string gVertexShaderSource =
    "#version 460 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
    "}\n";
const std::string gFragmentShaderSource =
     "#version 460 core\n"
     "out vec4 color;\n"
     "void main()\n"
     "{\n"
     "    color = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
     "}\n";

GLuint CompileShader(GLuint type, const std::string& source){
    GLuint shaderObject;
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }
    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexshadersource, const std::string& fragmentshadersource){
    GLuint programObject = glCreateProgram(); // "Program" = "Graphics Pipeline"
    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentshadersource);
    
    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);
    glValidateProgram(programObject);
    return  programObject;
}
void CreateGraphicsPipeline(){
    gGraphicsPipelineShadersProgram = CreateShaderProgram(gVertexShaderSource, gFragmentShaderSource);    
}


void GetOpenGLVersionInfo(){
    std::cout <<"Vendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
}


void VertexSpecification(){
     // lives on CPU
    const std::vector<GLfloat> vertexPosition{ //x, y, z
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };

    //start setting things for GPU
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // start generatibg VBO
    glGenBuffers(1,&gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GL_FLOAT),//target, size in bytes, data, usage
            vertexPosition.data(), GL_STATIC_DRAW ); 

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 0, (void*)0);//index, size, type, normalize, offset, pointer to first component
                                                            
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    
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


void PreDraw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,gScreenWidth,gScreenHeight);
    glClearColor(1.f,1.f,0.f,1.f);
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShadersProgram);
}

void Draw()
{
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, 3);
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
    
    VertexSpecification(); //set up geometry
    CreateGraphicsPipeline(); // vertex and fragment shader

    MainLoop();

    CleanUp();

    return 0;
}

