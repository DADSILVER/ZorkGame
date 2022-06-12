#pragma once
#include "creature.h"

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
	void take(const vector<string>& args);

public:

};

