#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL2/SDL.h>

#include <string>
#include <iostream>
#include "System.h"

System::System(const unsigned int screenWidth, const unsigned int screenHeight, const std::string strNameWindow ) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->window = 0;
    this->contextOpenGL = 0;
    this->strNameWindow = strNameWindow;
}

System::~System() {

}
        
void System::start() {
    bool finish(false);
    System::initializeSDLWindow();
    System::initializeOpenGLContext();

    while(!finish)
    {
        SDL_WaitEvent(&this->events);

        if(this->events.window.event == SDL_WINDOWEVENT_CLOSE)
            finish = true;
  
        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //Render quad
        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 0.f);
            glVertex2f(0.0f, 50.0f);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(100.f, 0.f);
            glColor3f(0.f, 1.f, 1.f);
            glVertex2f(100.f,  100.f);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(0.f,  100.f);
        glEnd();

        //Update screen
        SDL_GL_SwapWindow(this->window);
     }

    System::destroyOpenGLContext();
    System::destroySDLWindow();
}
    
void System::initializeSDLWindow() {
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Création de la fenêtre
    this->window = SDL_CreateWindow(this->strNameWindow.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);    

    if(this->window == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
}

void System::destroySDLWindow() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void System::initializeOpenGLContext() {
    // Set up the OpenGL's context
    this->contextOpenGL = SDL_GL_CreateContext(this->window);

    if(contextOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        System::destroySDLWindow();
    }

    /* Initialize OpenGL */
    glViewport(0.f, 0.f, this->screenWidth, this->screenHeight);

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0, this->screenWidth, this->screenHeight, 0.0, 1.0, -1.0);

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Check for error
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString(error));
    }
}

void System::destroyOpenGLContext() {
    SDL_GL_DeleteContext(this->contextOpenGL);
}
