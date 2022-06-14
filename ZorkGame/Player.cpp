#include <iostream>
#include "room.h"
#include "exit.h"
#include "player.h"
#include "NPC.h"
#include "Item.h"
#include "globals.h"

Player::Player(const char* name, const char* description, Room* room):
Creature(name, description, room), m_InvalidAction(false), m_LastMove("back")
{
	m_Type = PLAYER;
}

Player::~Player()
{
}


void Player::Look(const vector<string>& args) const
{
	if (args.size() == 1) 
	{
		cout << "\n" << m_Name << ", " << m_Description << "\n";
		m_Parent->Look(args);
	}
	else 
	{ 
		if(Same(args[1],"me"))
		{
			cout << "\n" << m_Name << ", " << m_Description << "\n";
			Inventory();
			Stats();
			return;
		}
		else
		{
			Entity* entity = Find(args[1], NPCAlly);
			if (entity != NULL) {
				entity->Look(args);
				return;
			}

			entity = Find(args[1], CREATURE);
			if (entity != NULL) {
				entity->Look(args);
				return;
			}

			entity = Find(args[1], ITEM);
			if (entity != NULL) {
				entity->Look(args);
				return;
			}

			entity = Find(args[1], ROOM);
			if (entity != NULL) {
				entity->Look(args);
				return;
			}

			cout << "\nThere is nothing here with name " << args[1] << ".\n";
		}
		
	}
}

bool Player::Go(const vector<string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);
	
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
	cout << "\nYou take direction " << exit->GetNameFrom(dynamic_cast<Room*>(m_Parent)) << "...\n";
	ChangeParentTo(exit->GetDestinationFrom(dynamic_cast<Room*>(m_Parent)));
	if (m_Helmet == nullptr && dynamic_cast<Room*>(m_Parent)->m_RoomType == RoomType::OCEAN)
	{
		cout << "\nIt's very dark you can't see anything.\n";
		return true;
	}
	m_Parent->Look(args);

	return true;
}

void Player::Talk(const vector<string>& args)
{
	NPC* persToTalk = dynamic_cast<NPC*> (m_Parent->Find(args[2], NPCAlly));

	if(persToTalk != nullptr)
	{
		persToTalk->talk();
	}
	else
	{
		cout << "\nDon't exist.\n";
	}
	
}

bool Player::Take(const vector<string>& args)
{
	if (args.size() == 2)
	{
		Item* item = dynamic_cast<Item*>(m_Parent->Find(args[1], ITEM));

		if (item == nullptr)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << args[1] << ".\n";
		item->ChangeParentTo(this);
		return true;
	}
	else
	{
		Item* item1 = dynamic_cast<Item*>(m_Parent->Find(args[3], ITEM));
		if (item1 == nullptr)
		{
			item1 = dynamic_cast<Item*>(m_Parent->Find(args[3], ITEM));
			if (item1 == nullptr)
			{
				cout << "\nThere is no item here with name " << item1->m_Name <<".\n";
				return false;
			}
		}

		Item* item2 = dynamic_cast<Item*>(item1->Find(args[1], ITEM));


		if (item2 == nullptr)
		{
			cout << "\nThere is no item here with name " << args[1] << ".\n";
			return false;
		}

		cout << "\nYou take " << args[1] << " from " << args[3] << ".\n";
		item2->ChangeParentTo(this);
		return true;
	}

}

void Player::Tick()
{
	if (m_InvalidAction)
	{
		DoDamage(2);
		m_InvalidAction = false;
	}

	if (m_CombatTarget != nullptr) {
		if (m_Parent->Find(m_CombatTarget) == true)
			MakeAttack();
		else
			m_CombatTarget = NULL;
	}
}

bool Player::CanDoAction(const vector<string>& args)
{
	if (dynamic_cast<Room*>(m_Parent)->m_RoomType == RoomType::OCEAN)
	{
		if (m_Helmet == nullptr)
		{
			if (args.size() == 1)
			{
				if (!(Same(args[0], "back") || Same(args[0], "b")))
				{
					m_InvalidAction = true;
					return false;
				}
			}
			else if(args.size() == 2)
			{
				if (!(Same(args[0], "go") || Same(args[1], "back")))
				{
					m_InvalidAction = true;
					return false;
				}
			}
		}
	}
	
	return true;
}

bool Player::DontSee() const
{
	//m_Player->look(args);
	cout << "\nIt's very dark you can't see anything.\n";
	cout << "\nSomething hit you.\n";
	cout << "You should go back.\n";
	return true;
}




