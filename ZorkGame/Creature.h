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
	Creature(const char* name, const char* description, Room* room, int hitPoints, int aggreLevel);
	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const override;
	virtual bool Take(const vector<string>& args);
	bool Drop(const vector<string>& args);
	bool Equip(const vector<string>& args);
	bool UnEquip(const vector<string>& args);
	virtual void Tick() override;
	void Inventory() const;
	bool Stats() const;
	bool Unlock(const vector<string>& args) const;
	bool Lock(const vector<string>& args) const;
	bool Attack(const vector<string>& args);
	int MakeAttack();
	virtual void Died() const;
	bool Loot(const vector<string>& args);
	int ReceiveAttack(int damage);
	void TakeDamage(int dmg);

	inline Room* GetRoom() const { return (Room*)(m_Parent); };
	inline bool PlayerInRoom() const { return m_Parent->Find(PLAYER) != nullptr; };
	inline bool IsAlive() const { return m_HitPoints > 0; };

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

