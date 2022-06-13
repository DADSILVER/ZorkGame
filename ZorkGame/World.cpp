#include <iostream>
#include "World.h"
#include "globals.h"
#include "entity.h"
#include "exit.h"
#include "Player.h"
#include "NPC.h"
#include "Item.h"

using namespace std;


World::World()
{

	// Create rooms
	Room* cptRoom = new Room("Captain room", "You are in a little room.", RoomType::NORMAL);
	Room* hall = new Room("Hall", "You are in a big room.", RoomType::NORMAL);
	Room* crewRoom = new Room("Crew room", "You are in a little room.", RoomType::NORMAL);
	Room* workRoom = new Room("Work room", "You are in Work room.", RoomType::NORMAL);
	Room* chD1 = new Room("Depressurization chamber A1", "You are in Depressurization chamber A1.", RoomType::NORMAL);
	Room* ocean1 = new Room("Ocean", "Water everywhere.", RoomType::OCEAN);
	//Room* room7 = new Room("Ocean", "It's very dark you can't see anything.");
	Room* chD2 = new Room("Depressurization chamber A2", "You are in Depressurization chamber A2.", RoomType::NORMAL);
	Room* infirmary = new Room("Infirmary", "You are in infirmary.", RoomType::NORMAL);

	//Add rooms
	entities.push_back(cptRoom);
	entities.push_back(hall);
	entities.push_back(crewRoom);
	entities.push_back(workRoom);
	entities.push_back(chD1);
	entities.push_back(ocean1);
	//entities.push_back(room7);
	entities.push_back(chD2);
	entities.push_back(infirmary);


	//Create Exits
	Exit* cptRoomHall = new Exit("south", "north", "Door", cptRoom, hall);
	Exit* hallCrewRoom = new Exit("south", "north", "Door", hall, crewRoom);
	Exit* hallWorkRoom = new Exit("west", "east", "Little path", hall, workRoom);
	hallWorkRoom->m_Locked = true;
	Exit* hallChD1 = new Exit("east", "west", "Door", hall, chD1);
	Exit* ocenaChD1 = new Exit("west", "east", "Robust door", ocean1, chD1);
	Exit* ocenaChD2 = new Exit("north", "south", "Robust door", ocean1, chD2);
	Exit* infirmaryChD2 = new Exit("south", "north", "Little path", infirmary, chD2);
	

	//Add Exits
	entities.push_back(cptRoomHall);
	entities.push_back(hallCrewRoom);
	entities.push_back(hallWorkRoom);
	entities.push_back(hallChD1);
	entities.push_back(ocenaChD1);
	entities.push_back(ocenaChD2);
	entities.push_back(infirmaryChD2);


	// Create NPC
	NPC* jonny = new NPC("Jonny", "Diving technician.", crewRoom);
	jonny->m_State = "Seriously injured";
	NPC* dolores = new NPC("Dolores", "Plant researcher.", crewRoom);
	dolores->m_State = "Trying to healt Jonny";
	dolores->m_Dialog = "I need more bandages. There is no more in the first aid kit. Go to the infirmary. HURRY UP!!!!";
	dolores->m_Talkable = true;

	//Add NPCs
	entities.push_back(jonny);
	entities.push_back(dolores);

	
	// Create creatures
	Creature* stranger = new Creature("Stranger", "Injured suspicious person.", infirmary);
	stranger->m_HitPoints = 14;
	stranger->m_MaxDamage = 2;
	Creature* eel = new Creature("Eel", "", ocean1);
	eel->m_HitPoints = 20;
	eel->m_MaxDamage = 4;
	

	//Add NPCs
	entities.push_back(stranger);
	entities.push_back(eel);


	// Create Items
	Item* key = new Item("Cardkey", "Open restricted areas.", cptRoom, ItemType::KEY);
	hallWorkRoom->m_Key = key;
	Item* box = new Item("Box", "there may be something inside.", workRoom, ItemType::COMMON);
	Item* knife = new Item("Knife", "can be used as a weapon.", box, ItemType::WEAPON);
	knife->m_MaxValue = 4;
	knife->m_MinValue = 3;
	Item* divingSuit = new Item("Diving-suit", "Needed to get out on the water. can be used as a skin.", workRoom, ItemType::SKIN);
	divingSuit->m_MaxValue = 2;
	divingSuit->m_MinValue = 2;
	Item* headLantern = new Item("Headlantern", "You can use as helmet to see in the drakness.", crewRoom, ItemType::LANTERN);
	Item* bandages = new Item("Bandages", "You can use to save Jonny.", stranger, ItemType::COMMON);


	//Add Items
	entities.push_back(key);
	entities.push_back(box);
	entities.push_back(knife);
	entities.push_back(divingSuit);
	entities.push_back(headLantern);

	// Add palyer
	m_Player = new Player("Captian", "You are the captain of the place", cptRoom);
	m_Player->m_HitPoints = 30;
	m_Player->m_MaxDamage = 3;
	entities.push_back(m_Player);

}

World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) 
	{
		delete* it;

	}

	entities.clear();
}

bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if (args.size() > 0 && args[0].length() > 0)
	{
		ret = ParseCommand(args);
	}

	GameLoop();

	return ret;
}

void World::GameLoop()
{
	clock_t now = clock();

	if ((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->tick();
		}

		tick_timer = now;
	}
}

bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;
	if (m_Player->m_Helmet == nullptr && dynamic_cast<Room*>(m_Player->m_Parent)->m_RoomType == RoomType::OCEAN) 
	{
		switch (args.size())
		{
			case 1: // commands with no arguments ------------------------------
			{
				if (same(args[0], "back") || same(args[0], "b"))
				{
					args.push_back(m_Player->m_LastMove);
					m_Player->go(args);
					return true;
				}
				break;
			}
			case 2: // commands with no arguments ------------------------------
			{
				if (same(args[1], "back"))
				{
					args[1] = m_Player->m_LastMove;
					m_Player->go(args);
					return true;
				}
				break;
			}
		}

		//m_Player->look(args);
		cout << "\nIt's very dark you can't see anything.\n";
		m_Player->m_HitPoints -= 2;
		cout << "\nSomething hit you.\n";
		cout << "You should go back.\n";
		return true;
				
	}
	switch (args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if (same(args[0], "look") || same(args[0], "l"))
			{
				m_Player->look(args);
			}
			else if (same(args[0], "north") || same(args[0], "n"))
			{
				args.push_back("north");
				m_Player->go(args);
			}
			else if (same(args[0], "south") || same(args[0], "s"))
			{
				args.push_back("south");
				m_Player->go(args);
			}
			else if (same(args[0], "east") || same(args[0], "e"))
			{
				args.push_back("east");
				m_Player->go(args);
			}
			else if (same(args[0], "west") || same(args[0], "w"))
			{
				args.push_back("west");
				m_Player->go(args);
			}
			else if (same(args[0], "stats") || same(args[0], "st"))
			{
				m_Player->stats();
			}
			else if (same(args[0], "inventory") || same(args[0], "i"))
			{
				m_Player->inventory();
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if (same(args[0], "look") || same(args[0], "l"))
			{
			}
			else if (same(args[0], "go"))
			{
				m_Player->go(args);
			}
			else if (same(args[0], "take") || same(args[0], "pick"))
			{
				m_Player->take(args);
			}
			else if (same(args[0], "drop") || same(args[0], "put"))
			{
				m_Player->drop(args);
			}
			else if (same(args[0], "equip") || same(args[0], "eq"))
			{
				m_Player->equip(args);
			}
			else if (same(args[0], "unequip") || same(args[0], "uneq"))
			{
				m_Player->unEquip(args);
			}
			else if (same(args[0], "examine") || same(args[0], "ex"))
			{
			}
			else if (same(args[0], "attack") || same(args[0], "at"))
			{
			}
			else if (same(args[0], "loot") || same(args[0], "lt"))
			{
			}
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			if (same(args[0], "talk") || same(args[0], "t"))
			{
				m_Player->talk(args);
			}
			else
				ret = false;
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if (same(args[0], "unlock") || same(args[0], "unlk"))
			{
				m_Player->unlock(args);
			}
			else if (same(args[0], "lock") || same(args[0], "lk"))
			{
				m_Player->lock(args);
			}
			else if (same(args[0], "take") || same(args[0], "pick"))
			{
				m_Player->take(args);
			}
			else if (same(args[0], "drop") || same(args[0], "put"))
			{

			}
			else
				ret = false;
			break;
		}
		default:
			ret = false;
	}

	return ret;
}
