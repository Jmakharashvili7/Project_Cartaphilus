#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include "GameScreenManager.h"

using namespace std;

// Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

// function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);

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
    }
        
    // Initialize renderer
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    // Check if the renderer was initialized
    if (g_renderer != nullptr)
    {
        // setup screen manager
        game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);

        // set the time
        g_old_time = SDL_GetTicks();

        // Init PNG loading
        int imageFlags = IMG_INIT_PNG;

        // Check if loading was successful
        if (!(IMG_Init(imageFlags) & imageFlags))
        {
            cout << "SDL_Image could not be initialized. Error: " << IMG_GetError();
            return false;
        }
    }
    // renderer was not initialized correctly
    else
    {
        cout << "Renderer could not initialize. Error: " << SDL_GetError();
        return false;
    }
    return true;
}

void CloseSDL()
{
    // release the window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // clean up screen manager
    delete game_screen_manager;
    game_screen_manager = nullptr;

    // quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    // release the renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;
}

bool Update()
{
    // time
    Uint32 new_time = SDL_GetTicks();

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

    game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);

    g_old_time = new_time;

    return false;
}

void Render()
{
    // Clear the screen
    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(g_renderer);

    game_screen_manager->Render();

    // update the screen
    SDL_RenderPresent(g_renderer);
}
