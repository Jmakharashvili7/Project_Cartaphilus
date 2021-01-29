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
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

// function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

int main(int argc, char* argv[])
{
    // check if the user wishes to quit
    bool quit = false; 

    // Check if SDL was initialized
    if (InitSDL())
    {
        // Game Loop
        while (!quit)
        {
            Render();
            quit = Update();
        }
    }
    CloseSDL();
    return 0;
}

bool InitSDL()
{
    // Check if initialization was successful
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL did not initialize. Error: " << SDL_GetError();
        return false;
    }
    // initialization was succesful
    else
    {
        // Create the window
        g_window = SDL_CreateWindow("Project Cartaphilus",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIHGT,
                SDL_WINDOW_SHOWN);
        // check if the window was created
        if (g_window == nullptr)
        {
            // window failed
            cout << "Window was not created. Error " << SDL_GetError();
            return false;
        }

        // Initialize renderer
        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

        // Check if the renderer was initialized
        if (g_renderer != nullptr)
        {
            // Init PNG loading
            int imageFlags = IMG_INIT_PNG;

            // Check if loading was successful
            if (!(IMG_Init(imageFlags) & imageFlags))
            {
                cout << "SDL_Image could not be initialized. Error: " << IMG_GetError();
                return false;
            }

            // load the background texture
            g_texture = LoadTextureFromFile("Images/test.bmp");
            if (g_texture == nullptr)
            {
                return false;
            }
        }
        // renderer was not initialized correctly
        else
        {
            cout << "Renderer could not initialize. Error: " << SDL_GetError();
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

    // clear the texture 
    FreeTexture();
    // release the renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;
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

void Render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_renderer);

    // set where to render the texture
    SDL_Rect renderLocation = {0, 0, SCREEN_WIDTH, SCREEN_HEIHGT};

    // render to the screen
    SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

    // update the screen
    SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
    // remove any memory used for the previous texture
    FreeTexture();

    SDL_Texture* p_texture = nullptr;

    // load the image
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    // check if the surface was loaded
    if (p_surface != nullptr)
    {
        // create the texture from the pixels on the surface
        p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
        if (p_texture == nullptr)
        {
            cout << "Unable to create texture from surface. Error: " << SDL_GetError();
        }
        // remove the loaded surface now that we have a texture
        SDL_FreeSurface(p_surface);
    }
    else
    {
        cout << "Unable to create texture from surface. Error: " << IMG_GetError();
    }

    // return the texture
    return p_texture;
}

void FreeTexture()
{
    // check if the texture exists before destroying it
    if (g_texture != nullptr)
    {
        SDL_DestroyTexture(g_texture);
        g_texture = nullptr;
    }
}