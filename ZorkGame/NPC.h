#pragma once
#include "Creature.h"
class NPC :
    public Creature
{
public:
    NPC(const char* name, const char* description, Room* room);
    ~NPC();

    void look(const vector<string>& args) const;

    virtual void talk();

public:
    
    bool m_Talkable;
    string m_Dialog;
    string m_State;
};

