#pragma once
#include "Entity.h"
#include <string.h>
#include "Room.h"

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
    Item(const char* name, const char* description, Room* room, ItemType itemType);
    ~Item();

    void look() const;

public:
    ItemType m_ItemType
};

