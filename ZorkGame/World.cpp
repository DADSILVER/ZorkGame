#include <iostream>
#include "World.h"
#include "globals.h"
#include "entity.h"


World::World()
{
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
			(args.size() == 1) ? args.push_back("north") : args[1] = "north";
		}
		else if (Same(args[0], "south") || Same(args[0], "s"))
		{
			(args.size() == 1) ? args.push_back("south") : args[1] = "south";
		}
		else if (Same(args[0], "east") || Same(args[0], "e"))
		{
			(args.size() == 1) ? args.push_back("east") : args[1] = "east";
		}
		else if (Same(args[0], "west") || Same(args[0], "w"))
		{
			(args.size() == 1) ? args.push_back("west") : args[1] = "west";
		}
		else if (Same(args[0], "up") || Same(args[0], "u"))
		{
			(args.size() == 1) ? args.push_back("up") : args[1] = "up";
		}
		else if (Same(args[0], "down") || Same(args[0], "d"))
		{
			(args.size() == 1) ? args.push_back("down") : args[1] = "down";
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
