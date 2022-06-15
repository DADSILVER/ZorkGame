#include <iostream>
#include "NPC.h"


NPC::NPC(const char* name, const char* description, Room* room, Item* item, int hitPoints):
	Creature(name, description, room, hitPoints, 0), m_MissionItem(nullptr)
{
	m_Type = NPCAlly;
	
	m_Talkable = false;
	m_Dialog = "";
	m_State = "";
	m_MissionItem = item;
	m_HitPoints = hitPoints;

}

void NPC::Look(const vector<string>& args) const
{
	if (IsAlive())
	{
		cout << "\n" << m_Name << ", ";
		cout << m_Description << "\n";
	}
	else
	{
		cout << m_Name << "'s corpse\n";
		cout << "Here lies dead: " << m_Description << "\n";
	}
	cout << m_State << "\n";
}

void NPC::talk()
{
    if(m_Talkable)
	{
		cout << "\n" << m_Dialog << "\n";
	}
	else
	{
		cout << "\nNothing to say.\n";
	}
}


