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

void Creature::Look(const vector<string>& args) const
{
	if (IsAlive())
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



bool Creature::Go(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->getExit(args[1]);

	if (exit == NULL)
		return false;

	if (PlayerInRoom())
		cout << m_Name << "goes " << args[1] << "...\n";

	//ChangeParentTo(exit->GetDestinationFrom((Room*)parent));

	return true;
}

Room* Creature::GetRoom() const
{
	return (Room*)m_Parent;
}

bool Creature::IsAlive() const
{
	return m_HitPoints > 0;
}
