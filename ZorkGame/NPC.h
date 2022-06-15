#pragma once
#include "Creature.h"
class NPC :
    public Creature
{
public:
    NPC(const char* name, const char* description, Room* room, Item* item, int hitPoints);
    ~NPC();

    void Look(const vector<string>& args) const override;

    void talk();

public:
    
    Item* m_MissionItem;
    bool m_Talkable;
    string m_Dialog;
    string m_State;
};

