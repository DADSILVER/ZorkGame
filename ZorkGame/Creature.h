#pragma once

#include <string>
#include <vector>
#include "Entity.h"


class Room;
class Item;

using namespace std;

class Creature :
    public Entity
{
public:
	Creature(const char* name, const char* description, Room* room, int aggreLevel);
	~Creature();

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const override;
	virtual bool Take(const vector<string>& args);
	virtual bool Drop(const vector<string>& args);
	virtual bool Equip(const vector<string>& args);
	virtual bool UnEquip(const vector<string>& args);
	virtual void Tick() override;
	virtual void Inventory() const;
	virtual bool Stats() const;
	virtual bool Unlock(const vector<string>& args) const;
	virtual bool Lock(const vector<string>& args) const;
	virtual bool Attack(const vector<string>& args);
	virtual int MakeAttack();
	virtual void Died() const;
	virtual bool Loot(const vector<string>& args);
	int ReceiveAttack(int damage);
	virtual void DoDamage(int dmg);

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;

public:

	int m_HitPoints;
	int m_MinDamage;
	int m_MaxDamage;
	int m_MinProtection;
	int m_MaxProtection;
	int m_AggreLevel;
	Creature* m_CombatTarget;

	Item* m_Weapon;
	Item* m_Skin;
	Item* m_Helmet;
};

