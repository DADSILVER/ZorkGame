#include <iostream>
#include "room.h"
#include "Exit.h"

// ----------------------------------------------------
Exit::Exit(const char* name, const char* oppositeName, const char* description, Room* origin, Room* destination, bool oneWay) :
	Entity(name, description, (Entity*)origin),
	M_closed(false), M_locked(false), M_key(NULL), M_oneWay(oneWay), M_destination(destination), M_oppositeName(oppositeName)
{
	M_type = EXIT;

	if (M_oneWay == false)
		destination->M_contains.push_back(this);
}

// ----------------------------------------------------
Exit::~Exit()
{
}


// ----------------------------------------------------
void Exit::Look() const
{
	cout << M_name << " to " << M_oppositeName << "\n";
	cout << M_description << "\n";
}