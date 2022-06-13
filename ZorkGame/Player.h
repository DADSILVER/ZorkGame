#pragma once
#include "creature.h"
#include <string.h>

using namespace std;


class Player :
    public Creature
{
public:
	Player(const char* name, const char* description, Room* room);
	~Player();

	void look(const vector<string>& args);
	bool go(const vector<string>& args);
	void talk(const vector<string>& args);
	bool take(const vector<string>& args);

public:
	string m_LastMove;

};

