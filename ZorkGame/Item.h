#pragma once
#include "Entity.h"
#include <string.h>
#include <vector>

using namespace std;

enum ItemType
{
    KEY,
    WEAPON,
    SKIN,
    COMMON
};

class Item :
    public Entity
{
public:
    Item(const char* name, const char* description, Entity* parent, ItemType itemType);
    ~Item();

    void look(const vector<string>& args) const;

public:
    int m_MinValue;
    int m_MaxValue;
    ItemType m_ItemType;
};

