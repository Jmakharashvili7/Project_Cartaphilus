#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_renderer = renderer;

	// Character information
	m_position = new Vector2D(start_position);
	m_collisionCirlce = new Circle2D(15.0f, m_position);
	m_velocity = new Vector2D(0, 0);

	// variables for user input
	m_facing_direction = FACING_RIGHT;
	m_moving_right = false;
	m_moving_left = false;
	m_can_jump = true;
	m_jumping = false;

	// setup texture
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cerr << "Character texture could not be loaded!" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

Circle2D* Character::GetCollisionCircle()
{
	return m_collisionCirlce;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(*m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(*m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{ 
	if (m_jumping)
	{
		m_position->y -= m_velocity->y * deltaTime;
	}
	ApplyGravity(deltaTime);

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	// Check input event type
    switch (e.type)
	{
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_SPACE:
			if (m_can_jump)
			{
				m_velocity->y = 0;
				m_velocity->y += JUMPHEIGHT;
				m_jumping = true;
				m_can_jump = false;
			}
			break;
        }
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
    }
}

void Character::SetPosition(Vector2D* new_position)
{
	m_position = new_position;
}

Vector2D* Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_position->x -= deltaTime * MOVESPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	m_position->x += deltaTime * MOVESPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::ApplyGravity(float deltaTime)
{
	if (m_position->y < 330)
	{
		m_velocity->y -= GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
		m_jumping = false;
	}
}

// Implement air resistance and terminal velocity. try to add a slide as well. make movement feel as good as possible.