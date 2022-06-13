#include <iostream>
#include "room.h"
#include "exit.h"
#include "player.h"
#include "NPC.h"
#include "Item.h"

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
	m_Parent->look(args);
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

	if ((exit->m_Destination->m_RoomType == RoomType::OCEAN || ((Room*)exit->m_Parent)->m_RoomType == RoomType::OCEAN) && m_Skin==nullptr) {
		cout << "\nYou need equip a diving suit.\n";
		return false;
	}

	if (args[1] == exit->m_OppositeName)
	{
		m_LastMove = exit->m_Name;
	}
	else
	{
		m_LastMove = exit->m_OppositeName;
	}
	cout << "\nYou take direction " << exit->getNameFrom(dynamic_cast<Room*>(m_Parent)) << "...\n";
	changeParentTo(exit->getDestinationFrom(dynamic_cast<Room*>(m_Parent)));
	if (m_Helmet == nullptr && dynamic_cast<Room*>(m_Parent)->m_RoomType == RoomType::OCEAN)
	{
		cout << "\nIt's very dark you can't see anything.\n";
		return true;
	}
	m_Parent->look(args);

	return true;
}

void Player::talk(const vector<string>& args)
{
	NPC* persToTalk = dynamic_cast<NPC*> (m_Parent->find(args[2], NPCAlly));

	if(persToTalk != nullptr)
	{
		persToTalk->talk();
	}
	else
	{
		cout << "\nDon't exist.\n";
	}
	
}

bool Player::take(const vector<string>& args)
{
	if (args.size() == 2)
	{
		Item* item = dynamic_cast<Item*>(m_Parent->find(args[1], ITEM));

		if (item == nullptr)
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
		Item* item1 = dynamic_cast<Item*>(m_Parent->find(args[3], ITEM));
		if (item1 == nullptr)
		{
			item1 = dynamic_cast<Item*>(m_Parent->find(args[3], ITEM));
			if (item1 == nullptr)
			{
				cout << "\nThere is no item here with that name.\n";
				return false;
			}
		}

		Item* item2 = dynamic_cast<Item*>(m_Parent->find(args[1], ITEM));


		if (item2 == nullptr)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << args[1] << " from " << args[3] << ".\n";
		item2->changeParentTo(this);
		return true;
	}

}


