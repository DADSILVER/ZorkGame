#include <iostream>
#include "room.h"
#include "exit.h"
#include "player.h"
#include "NPC.h"

Player::Player(const char* name, const char* description, Room* room):
Creature(name, description, room)
{
	m_Type = PLAYER;
}

Player::~Player()
{
}

void Player::look(const vector<string>& args)
{
	cout << "\n" << m_Name << "\n";
	cout << m_Description << "\n";
	m_Parent->look();
}

bool Player::go(const vector<string>& args)
{
	Exit* exit = getRoom()->getExit(args[1]);
	
	if (exit == NULL) {
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}
	
	if (exit->m_Locked)
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	cout << "\nYou take direction " << exit->getNameFrom((Room*)m_Parent) << "...\n";
	changeParentTo(exit->getDestinationFrom((Room*)m_Parent));
	m_Parent->look();

	return true;
}

void Player::talk(const vector<string>& args)
{
	NPC* persToTalk = (NPC*) m_Parent->find(args[2], NPCAlly);

	if(persToTalk != NULL)
	{
		persToTalk->talk();
	}
	else
	{
		cout << "\nDon't exist.\n";
	}
	
}

