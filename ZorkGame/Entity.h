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

		void Look() const;

		virtual void Tick();

	public:
		EntityType M_type;
		string M_name;
		string M_description;

		Entity* M_parent;
		list<Entity*> M_contains;

};

