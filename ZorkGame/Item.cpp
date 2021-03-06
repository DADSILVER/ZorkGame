#include <iostream>
#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent, ItemType itemType):
	Entity(name, description, parent)
{
	m_Type = ITEM;
	m_ItemType = itemType;
	m_MaxValue=0;
	m_MinValue=0;
}

void Item::Look(const vector<string>& args) const
{
	cout << "\n" << m_Name << ", ";
	cout << m_Description << "\n";

	// Find if the item contains other items
	list<Entity*> stuff;
	FindAll(ITEM, stuff);
	if (stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->m_Name << "\n";
	}
}