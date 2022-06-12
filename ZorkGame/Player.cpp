#include <iostream>
#include "room.h"
#include "exit.h"
#include "player.h"

Player::Player(const char* name, const char* description, Room* room):
Creature(name, description, room)
{
	m_Type = PLAYER;
}

Player::~Player()
{
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

void Player::look(const vector<string>& args) const
{
}
