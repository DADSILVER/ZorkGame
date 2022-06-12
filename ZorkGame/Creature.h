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

	virtual bool go(const vector<string>& args);
	virtual void look(const vector<string>& args) const;
	virtual void tick();
	virtual void inventory() const;
	virtual bool unlock(const vector<string>& args) const;

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

};

