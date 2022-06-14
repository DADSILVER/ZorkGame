#include <iostream>
#include "Creature.h"
#include "exit.h"
#include "room.h"
#include "Item.h"
#include "globals.h"



Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description, room)
{
	m_Type = CREATURE;
	m_HitPoints = 1;
	m_MinDamage = m_MaxDamage = m_MinProtection = m_MaxProtection = 0;
	m_CombatTarget = nullptr;
	m_Skin = nullptr;
	m_Weapon = nullptr;
	m_Helmet = nullptr;
}

Creature::~Creature()
{}

bool Creature::Go(const vector<string>& args)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
		return false;

	if (PlayerInRoom())
		cout << m_Name << "goes " << args[1] << "...\n";

	ChangeParentTo(exit->GetDestinationFrom((Room*)m_Parent));

	return true;
}

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

bool Creature::Take(const vector<string>& args)
{
	if (!IsAlive())
	{
		return false;
	}

	if(args.size() == 2)
	{
		Item* item = (Item*)m_Parent->Find(args[1], ITEM);

		if (item == NULL)
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
		Item* item1 = (Item*)m_Parent->Find(args[3], ITEM);
		if (item1 == NULL)
		{
			item1 = (Item*)this->Find(args[3], ITEM);
			if (item1 == NULL)
			{
				cout << "\nThere is no item here with that name.\n";
				return false;
			}
		}	

		Item* item2 = (Item*)item1->Find(args[1], ITEM);


		if (item2 == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << args[1] << " from " << args[3] <<".\n";
		item2->ChangeParentTo(this);
		return true;
	}

	
}

bool Creature::Drop(const vector<string>& args)
{
	Item* item = (Item*)this->Find(args[1], ITEM);

	if (item == NULL || item->m_Parent != this)
	{
		cout << "\nYou don't have this item.\n";
		return false;
	}

	cout << "\nYou drop " << args[1] << ".\n";

	if (item == m_Helmet)
	{
		m_Helmet = nullptr;
	}
	else if (item == m_Weapon)
	{
		m_MaxDamage -= m_Weapon->m_MaxValue;
		m_MinDamage -= m_Weapon->m_MinValue;
		m_Weapon = nullptr;
	}
	else if (item == m_Skin)
	{
		m_MaxDamage -= m_Skin->m_MaxValue;
		m_MinDamage -= m_Skin->m_MinValue;
		m_Skin = nullptr;
	}
	item->ChangeParentTo(this->m_Parent);

	return true;
}

bool Creature::Equip(const vector<string>& args)
{
	if (!IsAlive())
	{
		return false;
	}

	Item* item = (Item*)this->Find(args[1], ITEM);

	if (item == nullptr)
	{
		cout << "\nYou don't have this item.\n";
		return false;
	}

	if (item->m_ItemType == ItemType::SKIN)
	{
		if (item == m_Skin)
		{
			cout << "\nThe object was equipped.\n";
			return false;
		}
		
		m_Skin = item;
		m_MaxProtection += m_Skin->m_MaxValue;
		m_MinProtection += m_Skin->m_MinValue;
		cout << "\nItem " << m_Skin->m_Name << " equipped as skin.\n";
	}
	else  if(item->m_ItemType == ItemType::WEAPON)
	{
		if (item == m_Weapon)
		{
			cout << "\nThe object was equipped.\n";
			return false;
		}
		
		m_Weapon = item;
		m_MaxDamage += m_Weapon->m_MaxValue;
		m_MinDamage += m_Weapon->m_MinValue;
		cout << "\nItem " << m_Weapon->m_Name << " equipped as weapon.\n";
	}
	else  if (item->m_ItemType == ItemType::LANTERN)
	{
		if (item == m_Helmet)
		{
			cout << "\nThe object was equipped.\n";
			return false;
		}
		
		m_Helmet = item;
		cout << "\nItem " << m_Helmet->m_Name << " equipped as helmet.\n";
	}
	else
	{
		cout << "\nYou can't equip this item.\n";
		return false;
	}

	return true;
}

bool Creature::UnEquip(const vector<string>& args)
{
	if (!IsAlive())
	{
		return false;
	}

	Item* item = (Item*)this->Find(args[1], ITEM);

	if (item == NULL)
	{
		cout << "\nYou don't have this item.\n";
		return false;
	}

	if (item == m_Weapon) 
	{
		cout << "\nItem " << m_Name << " unequipped as weapon.\n";
		m_MaxDamage -= m_Weapon->m_MaxValue;
		m_MinDamage -= m_Weapon->m_MinValue;
		m_Weapon = NULL;
		
	}
	else if (item == m_Skin) 
	{
		cout << "\nItem " << m_Name << " unequipped as weapon.\n";
		m_MaxProtection -= m_Skin->m_MaxValue;
		m_MinProtection -= m_Skin->m_MinValue;
		m_Skin = NULL;
		
	}
	else
	{
		cout << "\nYou don't have equiped this item.\n";
		return false;
	}
	return true;

}

void Creature::Tick()
{
}

void Creature::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

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

bool Creature::Stats() const
{
	if (!IsAlive())
	{
		return false;
	}

	cout << "\n" << m_Name << " stats:\n";
	cout << " Hit points: " << m_HitPoints <<"\n";
	cout << " Damage: " << m_MaxDamage << " - "<< m_MinDamage << "\n";
	cout << " Damage: " << m_MaxProtection << " - " << m_MinProtection << "\n";

	return true;
}

bool Creature::Unlock(const vector<string>& args) const
{
	if (!IsAlive())
	{
		return false;
	}

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->m_Locked == false)
	{
		cout << "\nThat exit is not locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if (item == NULL)
	{
		cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (exit->m_Key != item)
	{
		cout << "\nKey '" << item->m_Name << "' is not the key for " << exit->GetNameFrom((Room*)m_Parent) << ".\n";
		return false;
	}

	cout << "\nYou unlock " << exit->GetNameFrom((Room*)m_Parent) << "...\n";

	exit->m_Locked = false;

	return true;
}

bool Creature::Lock(const vector<string>& args) const
{
	if (!IsAlive())
	{
		return false;
	}

	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		return false;
	}

	if (exit->m_Locked == true)
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	Item* item = (Item*)Find(args[3], ITEM);

	if (item == NULL)
	{
		cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
		return false;
	}

	if (exit->m_Key != item)
	{
		cout << "\nKey '" << item->m_Name << "' is not the key for " << exit->GetNameFrom((Room*)m_Parent) << ".\n";
		return false;
	}

	cout << "\nYou lock " << exit->GetNameFrom((Room*)m_Parent) << "...\n";

	exit->m_Locked = true;

	return true;
}

bool Creature::Attack(const vector<string>& args)
{
	Creature* target = (Creature*)m_Parent->Find(args[1], CREATURE);

	if (target == NULL)
		return false;

	m_CombatTarget = target;
	cout << "\n" << m_Name << " attacks " << target->m_Name << "!\n";
	return true;
}

int Creature::MakeAttack()
{
	if (!IsAlive() || !m_CombatTarget->IsAlive())
	{
		m_CombatTarget = m_CombatTarget->m_CombatTarget = NULL;
		return 0;
	}
	
	int result = Roll(m_MinDamage, m_MaxDamage);

	if (PlayerInRoom())
	{
		cout << m_Name << " attacks " << m_CombatTarget->m_Name << " for " << result << "\n";
	}

	m_CombatTarget->ReceiveAttack(result);

	if (m_CombatTarget->m_CombatTarget == NULL)
	{
		m_CombatTarget->m_CombatTarget = this;

	}
}

int Creature::ReceiveAttack(int damage)
{
	int prot = Roll(m_MinProtection, m_MaxProtection);
	int received = damage - prot;

	DoDamage(received);

	if (PlayerInRoom())
		cout << m_Name << " is hit for " << received << " damage (" << prot << " blocked) \n";

	if (IsAlive() == false)
	{
		cout << m_Name << " dies.\n";
	}

	return received;
}

void Creature::DoDamage(int dmg)
{
	m_HitPoints -= dmg;
}

Room* Creature::GetRoom() const
{
	return (Room*)m_Parent;
}

bool Creature::PlayerInRoom() const
{
	return m_Parent->Find(PLAYER) != NULL;
}

bool Creature::IsAlive() const
{
	return m_HitPoints > 0;
}
