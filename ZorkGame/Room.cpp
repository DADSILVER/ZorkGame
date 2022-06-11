#include <iostream>

#include "creature.h"
#include "room.h"

// ----------------------------------------------------
Room::Room(const char* name, const char* description) :
	Entity(name, description, NULL)
{
	M_type = ROOM;
}

// ----------------------------------------------------
Room::~Room()
{
}

// ----------------------------------------------------
void Room::Look() const
{
	cout << "\n" << M_name << "\n";
	cout << M_description;

	cout << "\n";
}
