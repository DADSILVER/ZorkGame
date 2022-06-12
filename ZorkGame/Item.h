#pragma once
#include "Entity.h"
#include <string.h>

using namespace std;

enum ItemType
{
    KEY,
    WEAPON,
    SKIN
};

class Item :
    public Entity
{
public:
    Item(const char* name, const char* description, Entity* parent, ItemType itemType);
    ~Item();

    void look() const;

public:
    ItemType m_ItemType;
};

