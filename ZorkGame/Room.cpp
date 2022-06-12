#include <iostream>

#include "creature.h"
#include "room.h"
#include "Exit.h"
#include "globals.h"
#include "NPC.h"


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

	//exits

	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		if ((*it)->m_Type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nDirection (" << ex->getNameFrom(this) << ") you see " << ex->getDestinationFrom(this)->m_Name;
		}
	}

	//NPC

	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		if ((*it)->m_Type == NPCAlly)
		{
			NPC* Npc = (NPC*)*it;
			Npc->look();
		}
	}

	cout << "\n";


}

Exit* Room::getExit(const string& direction) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); it++)
	{
		if ((*it)->m_Type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (same(ex->getNameFrom(this), direction))
				return ex;
		}
	}
	return nullptr;
}