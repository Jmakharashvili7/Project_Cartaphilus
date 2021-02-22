#pragma once
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <iostream>
#include "SDL.h"
#include "commons.h"
#include "Constants.h"
#include "Character.h"

class PhysicsManager
{
public:
	~PhysicsManager();

	static PhysicsManager* Instance();

	void ApplyGravity(Character* player, float deltaTime);
	bool circle(Circle2D* char1, Circle2D* char2);
	bool Box(Rect2D* rect1, Rect2D* rect2);
private:
	PhysicsManager();

	static PhysicsManager* m_instance;
};
#endif // PHYSICSMANAGER_H
