#include <iostream>
#include "World.h"
#include "globals.h"
#include "entity.h"

using namespace std;


World::World()
{

	// Create rooms
	Room* room1 = new Room("Captain room", "You are in a little room.");
	Room* room2 = new Room("Hall", "You are in a big room.");
	Room* room3 = new Room("Crew room", "You are in a little room.");
	Room* room4 = new Room("Work room", "You are in Work room.");
	Room* room5 = new Room("Depressurization chamber A1", "You are in Depressurization chamber A1.");
	Room* room6 = new Room("Ocean", "It's very dark you can't see anything.");
	Room* room7 = new Room("Ocean", "It's very dark you can't see anything.");
	Room* room8 = new Room("Depressurization chamber A2", "You are in Depressurization chamber A2.");
	Room* room9 = new Room("Infirmary", "You are in infirmary.");

	//Add rooms
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(room4);
	entities.push_back(room5);
	entities.push_back(room6);
	entities.push_back(room7);
	entities.push_back(room8);
	entities.push_back(room9);

}

//-------------------------------------------------------------------------

World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete* it;

	entities.clear();
}


//-------------------------------------------------------------------------

bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

//-------------------------------------------------------------------------

void World::GameLoop()
{
	clock_t now = clock();

	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

//-------------------------------------------------------------------------


bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch (args.size())
	{
	case 1: // commands with no arguments ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
		}
		else if (Same(args[0], "north") || Same(args[0], "n"))
		{
		}
		else if (Same(args[0], "south") || Same(args[0], "s"))
		{
		}
		else if (Same(args[0], "east") || Same(args[0], "e"))
		{
		}
		else if (Same(args[0], "west") || Same(args[0], "w"))
		{
		}
		else if (Same(args[0], "up") || Same(args[0], "u"))
		{
		}
		else if (Same(args[0], "down") || Same(args[0], "d"))
		{
		}
		else if (Same(args[0], "stats") || Same(args[0], "st"))
		{
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i"))
		{
		}
		else
			ret = false;
		break;
	}
	case 2: // commands with one argument ------------------------------
	{
		if (Same(args[0], "look") || Same(args[0], "l"))
		{
		}
		else if (Same(args[0], "go"))
		{
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
		}
		else if (Same(args[0], "equip") || Same(args[0], "eq"))
		{
		}
		else if (Same(args[0], "unequip") || Same(args[0], "uneq"))
		{
		}
		else if (Same(args[0], "examine") || Same(args[0], "ex"))
		{
		}
		else if (Same(args[0], "attack") || Same(args[0], "at"))
		{
		}
		else if (Same(args[0], "loot") || Same(args[0], "lt"))
		{
		}
		else
			ret = false;
		break;
	}
	case 3: // commands with two arguments ------------------------------
	{
		break;
	}
	case 4: // commands with three arguments ------------------------------
	{
		if (Same(args[0], "unlock") || Same(args[0], "unlk"))
		{
		}
		else if (Same(args[0], "lock") || Same(args[0], "lk"))
		{
		}
		else if (Same(args[0], "take") || Same(args[0], "pick"))
		{
		}
		else if (Same(args[0], "drop") || Same(args[0], "put"))
		{
		}
		else
			ret = false;
		break;
	}
	default:
		ret = false;
	}

	return ret;
}
