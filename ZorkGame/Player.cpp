#include <iostream>
#include "room.h"
#include "exit.h"
#include "player.h"
#include "NPC.h"
#include "Item.h"
#include "globals.h"

Player::Player(const char* name, const char* description, Room* room, int hitPoints):
Creature(name, description, room, hitPoints, 0), m_InvalidAction(false), m_LastMove("back"), m_IsMissionDone(false)
{
	m_Type = PLAYER;
}

void Player::Look(const vector<string>& args) const
{
	if (args.size() == 1) 
	{
		m_Parent->Look(args);
	}
	else 
	{ 
		if(globals::Same(args[1],"me"))
		{
			cout << "\n" << m_Name << ", " << m_Description << "\n";
			Inventory();
			Stats();
			return;
		}
		else
		{
			Entity* entity = m_Parent->Find(args[1], NPCAlly);
			if (entity != nullptr)
			{
				entity->Look(args);
				return;
			}

			entity = m_Parent->Find(args[1], CREATURE);
			if (entity != nullptr)
			{
				entity->Look(args);
				return;
			}

			entity = Find(args[1], ITEM);
			if (entity != nullptr)
			{
				entity->Look(args);
				return;
			}

			entity = m_Parent->Find(args[1], ITEM);
			if (entity != nullptr)
			{
				entity->Look(args);
				return;
			}

			if (globals::Same("room", args[1]))
			{
				m_Parent->Look(args);
				return;
			}

			cout << "\nThere is nothing here with name " << args[1] << ".\n";
		}
		
	}
}

bool Player::Go(const vector<string>& args)
{
	Exit* exit = GetRoom()->GetExit(args[1]);
	
	if (exit == nullptr) {
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}
	
	if (exit->m_Locked)
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	// Need equiped diving-suit to go a room with type OCEAN
	if ((exit->m_Destination->m_RoomType == RoomType::OCEAN || ((Room*)exit->m_Parent)->m_RoomType == RoomType::OCEAN) && m_Skin==nullptr) {
		cout << "\nYou need equip a diving suit.\n";
		return false;
	}

	// Save last move
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

	// Need headlantern to use Look()
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

	// Take item from room
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
	// Take item from other item or from room
	else
	{
		// Item in room
		Entity* item1 = dynamic_cast<Entity*>(m_Parent->Find(args[3], ITEM));
		if (item1 == nullptr)
		{
			// Item in other item
			item1 = dynamic_cast<Entity*>(Find(args[3], ITEM));
			if (item1 == nullptr)
			{
				cout << "\nThere is no item here with name " << args[3] <<".\n";
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
		TakeDamage(2);
		m_InvalidAction = false;
	}

	if (m_CombatTarget != nullptr) {
		if (m_Parent->Find(m_CombatTarget) == true)
		{
			MakeAttack();
		}
		else
		{
			m_CombatTarget = nullptr;
		}
	}
	for (list<Entity*>::iterator it = m_Contains.begin(); it != m_Contains.end(); ++it)
	{
		if ((*it)->m_Type != EXIT)
		{
			(*it)->Tick();
		}
	}
}

void Player::Died() const
{
	cout << m_Name << " dies.\n";
}

bool Player::IsMisionDone() const
{
	if (m_IsMissionDone) 
	{
		cout << " Good job. You save jonny.\n";
	}
	return m_IsMissionDone;
}

void Player::Give(const vector<string>& args)
{
	NPC* npc = dynamic_cast<NPC*>(m_Parent->Find(args[3], NPCAlly));
	if (npc == nullptr)
	{
		cout << "\nNone name " << args[3] << ".\n";
		return ;
	}

	Item* item = dynamic_cast<Item*>(Find(args[1], ITEM));


	if (item == nullptr)
	{
		cout << "\nThere is no item here with name " << args[1] << ".\n";
		return;
	}

	if (item != npc->m_MissionItem)
	{
		cout << args[3] << "\ndon't need " << args[1] << ".\n";
		return;
	}

	cout << "\nYou give " << args[1] << " to " << args[3] << ".\n";
	item->ChangeParentTo(npc);
	m_IsMissionDone = true;
	return;
}

bool Player::CanDoAction(const vector<string>& args) const
{
	if (dynamic_cast<Room*>(m_Parent)->m_RoomType == RoomType::OCEAN)
	{
		if (m_Helmet == nullptr)
		{
			if (args.size() == 1)
			{
				if (!(globals::Same(args[0], "back") || globals::Same(args[0], "b")))
				{
					return false;
				}
			}
			else if(args.size() == 2)
			{
				if (!(globals::Same(args[0], "go") || globals::Same(args[1], "back")))
				{	
					return false;
				}
			}
		}
	}
	
	return true;
}

bool Player::CantSee()
{
	m_InvalidAction = true;
	cout << "\nIt's very dark you can't see anything.\n";
	cout << "\nSomething hit you.\n";
	cout << "You should go back.\n";
	return true;
}




