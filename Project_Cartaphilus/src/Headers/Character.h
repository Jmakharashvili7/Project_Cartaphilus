#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "SDL.h"
#include "commons.h"
#include "Constants.h"

class Texture2D;

class Character
{
// variables
protected:
	SDL_Renderer* m_renderer;
	Vector2D* m_position;
	Vector2D* m_velocity;
	Texture2D* m_texture;
	Circle2D* m_collisionCirlce;
	// varibles to handle input
	bool m_moving_right;
	bool m_moving_left;
	bool m_can_jump;
	bool m_jumping;
private:
	DIRECTION m_facing_direction;
// functions
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~Character();

	Circle2D* GetCollisionCircle();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D* new_position);
	Vector2D* GetPosition();
protected:
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void ApplyGravity(float deltaTime);
};
#endif // CHARACTER_H

