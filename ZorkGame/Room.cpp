#include <iostream>

#include "creature.h"
#include "room.h"
#include "Exit.h"
#include "globals.h"


Room::Room(const char* name, const char* description) :
	Entity(name, description, NULL)
{
	m_Type = ROOM;
}

Room::~Room()
{
}



void Room::look() const
{
	cout << "\n" << m_Name << "\n";
	cout << m_Description;

	cout << "\n";
}

Exit* Room::getExit(const string& direction) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); it++)
	{
		if ((*it)->m_Type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (Same(ex->getNameFrom(this), direction))
				return ex;
		}
	}
	return nullptr;
}