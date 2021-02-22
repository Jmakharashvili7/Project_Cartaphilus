#include <iostream>
#include "FirstLevel.h"
#include "Texture2D.h"
#include "PhysicsManager.h"

FirstLevel::FirstLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupLevel();
	m_renderer = renderer;
	physicsManager = PhysicsManager::Instance();
}


FirstLevel::~FirstLevel()
{
	// clean up background texture
	delete m_background_texture;
	m_background_texture = nullptr;

	// clean up the character
	delete my_character;
	my_character = nullptr;
}

void FirstLevel::Render()
{
	// Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	// render character
	my_character->Render();
}

void FirstLevel::Update(float deltaTime, SDL_Event e)
{
	// Update character
	my_character->Update(deltaTime, e);
}

bool FirstLevel::SetupLevel()
{
	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));

	// load texture 
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load the background texture!" << std::endl;
		return false;
	}
	return true;
}
