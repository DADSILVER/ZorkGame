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
	Creature(const char* name, const char* description, Room* room);
	~Creature();

	virtual bool go(const vector<string>& args);
	virtual void look(const vector<string>& args) const;
	virtual bool take(const vector<string>& args);
	virtual bool drop(const vector<string>& args) const;
	virtual bool equip(const vector<string>& args);
	virtual void tick();
	virtual void inventory() const;
	virtual bool stats() const;
	virtual bool unlock(const vector<string>& args) const;
	virtual bool lock(const vector<string>& args) const;

	Room* getRoom() const;
	bool playerInRoom() const;
	bool isAlive() const;

public:

	int m_HitPoints;
	int m_MinDamage;
	int m_MaxDamage;
	int m_MinProtection;
	int m_MaxProtection;
	Creature* m_CombatTarget;

	Item* m_Weapon;
	Item* m_Skin;
};

