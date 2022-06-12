#pragma once

#include <string>
#include <vector>
#include "Entity.h"


class Room;

using namespace std;

class Creature :
    public Entity
{
public:
	Creature(const char* name, const char* description, Room* room);
	~Creature();

	virtual bool Go(const vector<string>& args);
	virtual void Look(const vector<string>& args) const;
	virtual void Tick();

	virtual void Die();
	virtual void Stats() const;

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;

public:

	int m_HitPoints;
	int m_MinDamage;
	int m_MaxDamage;
	int m_MinProtection;
	int m_MaxProtection;
	Creature* m_CombatTarget;
};

