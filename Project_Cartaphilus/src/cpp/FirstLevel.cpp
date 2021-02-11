#include <iostream>
#include "FirstLevel.h"
#include "Texture2D.h"

FirstLevel::FirstLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupLevel();
	m_renderer = renderer;
}

FirstLevel::~FirstLevel()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void FirstLevel::Render()
{
	// Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void FirstLevel::Update(float deltaTime, SDL_Event e)
{
}

bool FirstLevel::SetupLevel()
{
	// load texture 
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load the background texture!" << std::endl;
		return false;
	}
	return true;
}
