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
	for (list<Entity*>::iterator it = m_Contains.begin(); it != m_Contains.end(); ++it)
	{
		if ((*it)->m_Type != EXIT)
		{
			delete* it;
		}
	}

	m_Contains.clear();
}

void Room::Look(const vector<string>& args) const
{

	cout << "\n" << m_Name << ", " << m_Description << "\n";
 
	//NPCs

	list<Entity*> npcs;
	list<Entity*> creatures;
	list<Entity*> items;
	list<Entity*> exits;

	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it) {
		//NPCs

		if ((*it)->m_Type == NPCAlly)
		{
			npcs.push_back(*it);
		}
		if ((*it)->m_Type == CREATURE)
		{
			creatures.push_back(*it);
		}
		if ((*it)->m_Type == ITEM)
		{
			items.push_back(*it);
		}
		if ((*it)->m_Type == EXIT)
		{
			exits.push_back(*it);
		}
	}

	cout << "\nNPCs:";
	for (list<Entity*>::const_iterator it = npcs.begin(); it != npcs.cend(); ++it) {
		(*it)->Look(args);
	}

	//Creatures
	cout << "\nCreatures:";
	for (list<Entity*>::const_iterator it = creatures.begin(); it != creatures.cend(); ++it) {
		(*it)->Look(args);
	}

	//Items
	cout << "\nItems:";
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
		(*it)->Look(args);
	}

	//exits
	cout << "\nExits: ";
	for (list<Entity*>::const_iterator it = exits.begin(); it != exits.cend(); ++it) {
		Exit* ex = (Exit*)*it;
		cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->m_Name << " " << ex->m_Description;
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