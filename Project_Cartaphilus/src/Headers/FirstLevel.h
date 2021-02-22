#pragma once
#ifndef _FIRSTLEVEL_H
#define _FIRSTLEVEL_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"

class Texture2D;	
class Character;
class PhysicsManager;

class FirstLevel : GameScreen
{
private:
	Texture2D* m_background_texture;
	Character* my_character;
	PhysicsManager* physicsManager;
public:
	FirstLevel(SDL_Renderer* renderer);
	~FirstLevel();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private: 
	bool SetupLevel();	
};
#endif //_FIRSTLEVEL_H

