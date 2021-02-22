#pragma once
#ifndef COMMONS_H
#define COMMONS_H

#include <string>

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Rect2D
{
	Vector2D* position;
	float height, width;

	Rect2D(Vector2D* position, float width, float height)
	{
		this->position = position;
		this->width = width;
		this->height = height;
	}
	~Rect2D()
	{
		delete position;
	}
};

struct Circle2D
{
	float radius;
	Vector2D* center;

	Circle2D(float r, Vector2D* center)
	{
		radius = r;
		this->center = center;
	}
	~Circle2D()
	{
		delete center;
	}
};

enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum DIRECTION
{
	FACING_LEFT,
	FACING_RIGHT,
	FACING_UP,
	FACING_DOWN
};

enum TILETYPE
{
	WALL,
	FLOOR,
	EMPTY,
	POWERUP
};

struct Tile
{
	Rect2D* collisionBox;
	Vector2D* center;
	TILETYPE type;

	~Tile() 
	{
		delete collisionBox;
		delete center;
	}
};
#endif // COMMONS_H
