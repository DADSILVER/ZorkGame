#include <iostream>

#include "creature.h"
#include "room.h"
#include "Exit.h"
#include "globals.h"
#include "NPC.h"
#include "Item.h"


Room::Room(const char* name, const char* description, const RoomType roomType) :
	Entity(name, description, nullptr)
{
	m_Type = ROOM;
	m_RoomType = roomType;
}

Room::~Room()
{
}

void Room::Look(const vector<string>& args) const
{

	cout << "\n" << m_Name << ", " << m_Description << "\n";
 
	//NPCs

	cout << "\nNPCs:";
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		//NPCs

		if ((*it)->m_Type == NPCAlly)
		{
			(*it)->Look(args);
		}
	}

	//Creatures
	cout << "\nCreatures:";
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		//Creatures

		if ((*it)->m_Type == CREATURE)
		{
			(*it)->Look(args);
		}
	}

	//Items
	cout << "\nItems:";
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		if ((*it)->m_Type == ITEM)
		{
			(*it)->Look(args);
		}
	}

	//exits
	cout << "\nExits: ";
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		if ((*it)->m_Type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->m_Name << " " << ex->m_Description;
		}
	}

	cout << "\n";


}

Exit* Room::GetExit(const string& direction) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); it++)
	{
		if ((*it)->m_Type == EXIT)
		{
			Exit* ex = dynamic_cast<Exit*>(*it);
			if (globals::Same(ex->GetNameFrom(this), direction))
				return ex;
		}
	}
	return nullptr;
}