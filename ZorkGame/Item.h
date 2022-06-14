#pragma once
#include "Entity.h"
#include <string.h>
#include <vector>

using namespace std;

enum class ItemType
{
    KEY,
    WEAPON,
    SKIN,
    COMMON,
    LANTERN,
    CONTAINER
};

class Item :
    public Entity
{
public:
    Item(const char* name, const char* description, Entity* parent, ItemType itemType);
    ~Item();

    void Look(const vector<string>& args) const override;

public:
    int m_MinValue;
    int m_MaxValue;
    ItemType m_ItemType;
};

