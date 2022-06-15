#pragma once

#include <string>
#include <list>
#include <time.h>
#include <vector>

#include "Room.h"


#define TICK_FREQUENCY 0.5f

using namespace std;

class Entity;
class Player;

class World
{
public:
	static World& getInstance()
	{		
		static World  m_instance;
		return m_instance;
	}

public:
	World(World const&) = delete;
	void operator=(World const&) = delete;
	
	~World();
	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();
	bool IsGameFinished() const;
	bool IsInCombat() const;
	bool Help() const;

private:
	World();

private:

	
	clock_t tick_timer;
	list<Entity*> m_Entities;
	Player* m_Player;
	
};

