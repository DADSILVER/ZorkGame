#include <iostream>
#include "Creature.h"
#include "exit.h"
#include "room.h"



Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description, (Entity*)room)
{
	m_Type = CREATURE;
	m_HitPoints = 1;
	m_MinDamage = m_MaxDamage = m_MinProtection = m_MaxProtection = 0;
	m_CombatTarget = NULL;

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
