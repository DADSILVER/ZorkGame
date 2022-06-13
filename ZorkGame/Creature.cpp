#include <iostream>
#include "Creature.h"
#include "exit.h"
#include "room.h"
#include "Item.h"



Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description, (Entity*)room)
{
	m_Type = CREATURE;
	m_HitPoints = 1;
	m_MinDamage = m_MaxDamage = m_MinProtection = m_MaxProtection = 0;
	m_CombatTarget = NULL;
	m_Skin = NULL;
	m_Weapon = NULL;
}

Creature::~Creature()
{}

void Creature::look(const vector<string>& args) const
{
	if (isAlive())
	{
		cout << m_Name << "\n";
		cout << m_Description << "\n";
	}
	else
	{
		cout << m_Name << "'s corpse\n";
		cout << "Here lies dead: " << m_Description << "\n";
	}
}

bool Creature::take(const vector<string>& args)
{
	if (!isAlive())
	{
		return false;
	}

	if(args.size() == 2)
	{
		Item* item = (Item*)m_Parent->find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << args[1] << ".\n";
		item->changeParentTo(this);
		return true;
	}
	else
	{
		Item* item1 = (Item*)m_Parent->find(args[3], ITEM);
		if (item1 == NULL)
		{
			item1 = (Item*)this->find(args[3], ITEM);
			if (item1 == NULL)
			{
				cout << "\nThere is no item here with that name.\n";
				return false;
			}
		}	

		Item* item2 = (Item*)item1->find(args[1], ITEM);


		if (item2 == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << args[1] << " from " << args[3] <<".\n";
		item2->changeParentTo(this);
		return true;
	}

	
}

bool Creature::drop(const vector<string>& args) const
{
	Item* item = (Item*)this->find(args[1], ITEM);

	if (item == NULL || item->m_Parent != this)
	{
		cout << "\nYou don't have this item.\n";
		return false;
	}

	cout << "\nYou drop " << args[1] << ".\n";
	item->changeParentTo(this->m_Parent);

	return true;
}

bool Creature::equip(const vector<string>& args)
{
	if (!isAlive())
	{
		return false;
	}

	Item* item = (Item*)this->find(args[1], ITEM);

	if (item == NULL)
	{
		cout << "\nYou don't have this item.\n";
		return false;
	}

	if (item->m_ItemType = SKIN) 
	{
		cout << "\nItem " << m_Name << " equiped as skin.\n";
		m_Skin = item;
	}
	else  if(item->m_ItemType = WEAPON)
	{
		cout << "\nItem " << m_Name << " equiped as weapon.\n";
		m_Weapon = item;
	}
	else
	{
		cout << "\nYou can't equip this item.\n";
		return false;
	}

	return true;
}

void Creature::tick()
{
}

void Creature::inventory() const
{
	list<Entity*> items;
	findAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << "\n" << m_Name << " does not own any items\n";
		return;
	}

	cout << "\n" << m_Name << " owns:\n";
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		cout << (*it)->m_Name << "\n";
	}
}

bool Creature::stats() const
{
	if (!isAlive())
	{
		return false;
	}

	cout << "\n" << m_Name << " stats:\n";
	cout << " Hit points: " << m_HitPoints <<"\n";
	cout << " Damage: " << m_MaxDamage << " - "<< m_MinDamage << "\n";
	cout << " Damage: " << m_MaxProtection << " - " << m_MinProtection << "\n";

	return true;
}

bool Creature::unlock(const vector<string>& args) const
{
	if (!isAlive())
	{
		return false;
	}

	Exit* exit = getRoom()->getExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->m_Locked == false)
	{
		cout << "\nThat exit is not locked.\n";
		return false;
	}

	Item* item = (Item*)find(args[3], ITEM);

	if (item == NULL)
	{
		cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (exit->m_Key != item)
	{
		cout << "\nKey '" << item->m_Name << "' is not the key for " << exit->getNameFrom((Room*)m_Parent) << ".\n";
		return false;
	}

	cout << "\nYou unlock " << exit->getNameFrom((Room*)m_Parent) << "...\n";

	exit->m_Locked = false;

	return true;
}

bool Creature::lock(const vector<string>& args) const
{
	if (!isAlive())
	{
		return false;
	}

	Exit* exit = getRoom()->getExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->m_Locked == true)
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	Item* item = (Item*)find(args[3], ITEM);

	if (item == NULL)
	{
		cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (exit->m_Key != item)
	{
		cout << "\nKey '" << item->m_Name << "' is not the key for " << exit->getNameFrom((Room*)m_Parent) << ".\n";
		return false;
	}

	cout << "\nYou lock " << exit->getNameFrom((Room*)m_Parent) << "...\n";

	exit->m_Locked = true;

	return true;
}

bool Creature::go(const vector<string>& args)
{
	if (!isAlive())
		return false;

	Exit* exit = getRoom()->getExit(args[1]);

	if (exit == NULL)
		return false;

	if (playerInRoom())
		cout << m_Name << "goes " << args[1] << "...\n";

	changeParentTo(exit->getDestinationFrom((Room*)m_Parent));

	return true;
}

Room* Creature::getRoom() const
{
	return (Room*)m_Parent;
}

bool Creature::playerInRoom() const
{
	return m_Parent->find(PLAYER) != NULL;
}

bool Creature::isAlive() const
{
	return m_HitPoints > 0;
}
