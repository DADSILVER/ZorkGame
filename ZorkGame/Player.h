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

	bool Go(const vector<string>& args) override;
	void Talk(const vector<string>& args);
	void Look(const vector<string>& args) const override;
	bool Take(const vector<string>& args) override;
	void Tick() override;
	virtual bool CanDoAction(const vector<string>& args);
	virtual bool DontSee() const;
	virtual void DoDamage(int dmg);

public:
	string m_LastMove;

private:
	bool m_InvalidAction;

};

