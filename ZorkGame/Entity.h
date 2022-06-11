#pragma once

#include <string>
#include <list>


using namespace std;
enum EntityType
{
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	PLAYER
};


class Entity
{
	public:
		Entity(const char* name, const char* description, Entity* parent);
		virtual ~Entity();

		virtual void Tick();

	public:
		EntityType type;
		string name;
		string description;

		Entity* parent;
		list<Entity*> contains;

};

