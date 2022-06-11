#include <iostream>

#include "creature.h"
#include "room.h"

Room::Room(const char* name, const char* description) :
Entity(name, description, NULL)
{
	type = ROOM;
}

Room::~Room()
{
}
