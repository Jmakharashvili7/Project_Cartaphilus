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

int main(int argc, char* argv[])
{
    if (InitSDL())
    {
        SDL_Delay(5000);
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
