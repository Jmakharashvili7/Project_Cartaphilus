// Project_Cartaphilus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"

using namespace std;

// Globals
SDL_Window* g_window = nullptr;

// function prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* argv[])
{
    // check if the user wishes to quit
    bool quit = false; 

    // Check if SDL was initialized
    if (InitSDL())
    {
        while (!quit)
        {
            quit = Update();
        }
    }
    CloseSDL();
    return 0;
}

bool InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initialize. Error: " << SDL_GetError();
        return false;
    }
    else
    {
        // create window
        g_window = SDL_CreateWindow("Project Cartaphilus",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIHGT,
                SDL_WINDOW_SHOWN);
        // check if the window was created?
        if (g_window == nullptr)
        {
            // window failed
            cout << "Window was not created. Error " << SDL_GetError();
            return false;
        }
    }
    return true;
}

void CloseSDL()
{
    // release the window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

bool Update()
{
    // Event handler
    SDL_Event e;

    // Get events
    SDL_PollEvent(&e);

    switch (e.type)
    {
        // Click the 'X' to quit
    case SDL_QUIT:
        return true;
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
        case SDLK_q:
            return true;
            break;
        }
    }

    return false;
}