#pragma once

#include <string>
#include <list>
#include <time.h>
#include <vector>

#include "Room.h"


#define TICK_FREQUENCY 0.5f

using namespace std;

class Entity;

class World
{
public:

	World();
	~World();

	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();

private:

	clock_t tick_timer;
	list<Entity*> entities;
	
};

