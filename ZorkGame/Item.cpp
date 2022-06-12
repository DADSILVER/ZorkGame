#include <iostream>
#include "Item.h"

Item::Item(const char* name, const char* description, Room* room, ItemType itemType):
	Entity(name, description, room)
{
	m_Type = ITEM;
	m_ItemType = itemType;
}

Item::~Item()
{
}

void Item::look() const
{
	cout << "\n" << m_Name << "\n";
	cout << m_Description << "\n";

	list<Entity*> stuff;
	findAll(ITEM, stuff);

	if (stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->m_Name << "\n";
	}
}