#pragma once
#include "creature.h"
#include <string.h>

using namespace std;


class Player :
    public Creature
{
public:
	Player(const char* name, const char* description, Room* room, int hitPoints);
	~Player();

	bool Go(const vector<string>& args) override;
	void Talk(const vector<string>& args);
	void Look(const vector<string>& args) const override;
	bool Take(const vector<string>& args) override;
	void Tick() override;
	void Died() const override;
	bool IsMisionDone() const;
	void Give(const vector<string>& args);
	bool CanDoAction(const vector<string>& args) const;
	bool CantSee();
	

public:
	string m_LastMove;
	

private:
	bool m_IsMissionDone;
	bool m_InvalidAction;

};

