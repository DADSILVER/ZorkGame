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
	m_Entities.push_back(cptRoom);
	m_Entities.push_back(hall);
	m_Entities.push_back(crewRoom);
	m_Entities.push_back(workRoom);
	m_Entities.push_back(chD1);
	m_Entities.push_back(ocean1);
	//entities.push_back(room7);
	m_Entities.push_back(chD2);
	m_Entities.push_back(infirmary);


	//Create Exits
	Exit* cptRoomHall = new Exit("south", "north", "door", cptRoom, hall);
	Exit* hallCrewRoom = new Exit("south", "north", "door", hall, crewRoom);
	Exit* hallWorkRoom = new Exit("west", "east", "door with card reader", hall, workRoom);
	hallWorkRoom->m_Locked = true;
	Exit* hallChD1 = new Exit("east", "west", "door", hall, chD1);
	Exit* ocenaChD1 = new Exit("west", "east", "robust door", ocean1, chD1);
	Exit* ocenaChD2 = new Exit("north", "south", "robust door", ocean1, chD2);
	Exit* infirmaryChD2 = new Exit("south", "north", "door", infirmary, chD2);
	

	//Add Exits
	m_Entities.push_back(cptRoomHall);
	m_Entities.push_back(hallCrewRoom);
	m_Entities.push_back(hallWorkRoom);
	m_Entities.push_back(hallChD1);
	m_Entities.push_back(ocenaChD1);
	m_Entities.push_back(ocenaChD2);
	m_Entities.push_back(infirmaryChD2);


	// Create NPC
	NPC* jonny = new NPC("Jonny", "Diving technician.", crewRoom,nullptr);
	jonny->m_State = "Seriously injured";
	jonny->m_HitPoints = 10;
	jonny->m_MaxDamage = 3;
	NPC* dolores = new NPC("Dolores", "Plant researcher.", crewRoom, nullptr);
	dolores->m_State = "Trying to healt Jonny";
	dolores->m_Dialog = "I need more bandages. There is no more in the first aid kit. Go to the infirmary. HURRY UP!!!!";
	dolores->m_Talkable = true;
	dolores->m_HitPoints = 15;
	dolores->m_MaxDamage = 3;

	//Add NPCs
	m_Entities.push_back(jonny);
	m_Entities.push_back(dolores);

	
	// Create creatures
	Creature* stranger = new Creature("Stranger", "Injured suspicious person.", infirmary, 5);
	stranger->m_HitPoints = 14;
	stranger->m_MaxDamage = 2;
	Creature* eel = new Creature("Eel", "can be aggressive", hall,30);
	eel->m_HitPoints = 15;
	eel->m_MaxDamage = 3;
	

	//Add NPCs
	m_Entities.push_back(stranger);
	m_Entities.push_back(eel);


	// Create Items
	Item* key = new Item("Cardkey", "Open restricted areas.", cptRoom, ItemType::KEY);
	hallWorkRoom->m_Key = key;
	Item* box = new Item("Box", "there may be something inside.", workRoom, ItemType::CONTAINER);
	Item* knife = new Item("Knife", "can be used as a weapon.", box, ItemType::WEAPON);
	knife->m_MaxValue = 4;
	knife->m_MinValue = 3;
	Item* divingSuit = new Item("Diving-suit", "Needed to get out on the water. can be used as a skin.", workRoom, ItemType::SKIN);
	divingSuit->m_MaxValue = 2;
	divingSuit->m_MinValue = 2;
	Item* headLantern = new Item("Headlantern", "You can use as helmet to see in the drakness.", crewRoom, ItemType::LANTERN);
	Item* bandages = new Item("Bandages", "You can use to save Jonny.", stranger, ItemType::COMMON);
	dolores->m_MissionItem = bandages;

	//Add Items
	m_Entities.push_back(key);
	m_Entities.push_back(box);
	m_Entities.push_back(knife);
	m_Entities.push_back(divingSuit);
	m_Entities.push_back(headLantern);
	m_Entities.push_back(bandages);

	// Add palyer
	m_Player = new Player("Captian", "You are the captain of the place.", cptRoom);
	m_Player->m_HitPoints = 30;
	m_Player->m_MaxDamage = 3;
	m_Entities.push_back(m_Player);

}

World::~World()
{
	for (list<Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
	{
		delete* it;
	}

	m_Entities.clear();
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
		for (list<Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
		{
			(*it)->Tick();
		}

		tick_timer = now;
	}
}

bool World::IsGameFinished() const
{
	if (!m_Player->IsAlive())
	{		
		return true;
	}
	if (m_Player->IsMisionDone())
	{
		return true;
	}
	return false;
}

bool World::IsInCombat() const
{
	return m_Player->m_CombatTarget != nullptr;
}

bool World::Help() const
{
	cout << "\n\nExample: \n";
	cout << "'Look' or 'l' to see the room.\n";
	cout << "'Look [something]' or 'l [something]' to see [something] name and description.\n";
	cout << "'[orientation]' or 'go [orientation]' player go to the [orientation].\n";
	cout << "'back', 'b' or 'go back' player go to the previous room.\n";
	cout << "'stats' or 'st' to see player stats.\n";
	cout << "'inventory' or 'i' to see player inventory.\n";
	cout << "'stats' or 'st' to see player stats.\n";
	cout << "'inventory' or 'i' to see player inventory.\n";
	cout << "'take [item]' or 'pick [item]' player take the [item] form the room.\n";
	cout << "'take [item] from [item]' or 'pick [item] from [item]' player take the [item] from other [item].\n";
	cout << "'drop [item]' or 'put [item]' player drop the object in the room.\n";
	cout << "'drop [item] from [item]' or 'put [item] from [item]' player drop the [item] in other [item].\n";
	cout << "'equip [item]' or 'eq [item]' player equip the [item] to the player.\n";
	cout << "'unequip [item]' or 'uneq [item]' player unequip the [item] to the player.\n";
	cout << "'attack [Creature]' or 'at [Creature]' player attack the [Creature].\n";
	cout << "'loot [Creature]' or 'lt [Creature]' player take all the [items] from the [Creature].\n";
	cout << "'talk to [NPC]' player talk to the [NPC].\n";
	cout << "'unlock [orientation] with [item]' or 'unlk [orientation] with [item]' player unlock the [orientation] with the [item].\n";
	cout << "'lock [orientation] with [item]' or 'lk [orientation] with [item]' player lock the [orientation] with the [item].\n";
	cout << "'give [item] to [NPC]' or 'g [item] to [NPC]' player give the [item] to the [NPC].\n\n";
	
	return true;
}

bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;
	if (!m_Player->CanDoAction(args))
	{
		return m_Player->CantSee();			
	}
	switch (args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if (Same(args[0], "help") || Same(args[0], "h"))
			{
				Help();
			}
			else if (Same(args[0], "look") || Same(args[0], "l"))
			{
				m_Player->Look(args);
			}
			else if (Same(args[0], "back") || Same(args[0], "b"))
			{
				args.push_back(m_Player->m_LastMove);
				m_Player->Go(args);
			}
			else if (Same(args[0], "north") || Same(args[0], "n"))
			{
				args.push_back("north");
				m_Player->Go(args);
			}
			else if (Same(args[0], "south") || Same(args[0], "s"))
			{
				args.push_back("south");
				m_Player->Go(args);
			}
			else if (Same(args[0], "east") || Same(args[0], "e"))
			{
				args.push_back("east");
				m_Player->Go(args);
			}
			else if (Same(args[0], "west") || Same(args[0], "w"))
			{
				args.push_back("west");
				m_Player->Go(args);
			}
			else if (Same(args[0], "stats") || Same(args[0], "st"))
			{
				m_Player->Stats();
			}
			else if (Same(args[0], "inventory") || Same(args[0], "i"))
			{
				m_Player->Inventory();
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if (Same(args[0], "look") || Same(args[0], "l"))
			{
				m_Player->Look(args);
			}
			else if (Same(args[0], "go"))
			{
				if (Same(args[1], "back"))
				{
					args[1] = m_Player->m_LastMove;
				}
				m_Player->Go(args);
			}
			else if (Same(args[0], "take") || Same(args[0], "pick"))
			{
				m_Player->Take(args);
			}
			else if (Same(args[0], "drop") || Same(args[0], "put"))
			{
				m_Player->Drop(args);
			}
			else if (Same(args[0], "equip") || Same(args[0], "eq"))
			{
				m_Player->Equip(args);
			}
			else if (Same(args[0], "unequip") || Same(args[0], "uneq"))
			{
				m_Player->UnEquip(args);
			}
			else if (Same(args[0], "attack") || Same(args[0], "at"))
			{
				m_Player->Attack(args);
			}
			else if (Same(args[0], "loot") || Same(args[0], "lt"))
			{
				m_Player->Loot(args);
			}
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			if (Same(args[0], "talk") || Same(args[0], "t"))
			{
				m_Player->Talk(args);
			}
			else
				ret = false;
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if (Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				m_Player->Unlock(args);
			}
			else if (Same(args[0], "lock") || Same(args[0], "lk"))
			{
				m_Player->Lock(args);
			}
			else if (Same(args[0], "take") || Same(args[0], "pick"))
			{
				m_Player->Take(args);
			}
			else if (Same(args[0], "drop") || Same(args[0], "put"))
			{
				m_Player->Drop(args);
			}
			else if (Same(args[0], "give") || Same(args[0], "g"))
			{
				m_Player->Give(args);
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
