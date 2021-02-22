#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::m_instance = nullptr;


void PhysicsManager::ApplyGravity(Character* player, float deltaTime)
{
	//if (!player->GetPosition().floor)
		//playerPos.y -= m_gravity_constant;
}

PhysicsManager::~PhysicsManager()
{
	m_instance = nullptr;
}

PhysicsManager* PhysicsManager::Instance()
{
	if (!m_instance)
	{
		m_instance = new PhysicsManager;
	}
	return m_instance;
}

bool PhysicsManager::circle(Circle2D* char1, Circle2D* char2)
{
	Vector2D vec = Vector2D((char1->center->x - char2->center->x),
		(char1->center->y - char2->center->y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = double(char1->radius + char2->radius);

	return distance < combined_distance;
}

bool PhysicsManager::Box(Rect2D* rect1, Rect2D* rect2)
{
	if (rect1->position->x + (rect1->width / 2) > rect2->position->x &&
		rect1->position->x + (rect1->width / 2) < rect2->position->x + rect2->width &&
		rect1->position->y + (rect1->height / 2) > rect2->position->y &&
		rect1->position->y + (rect1->width / 2) < rect2->position->y + rect2->height)
	{
		return true;
	}
	return false;
}

PhysicsManager::PhysicsManager() {}
