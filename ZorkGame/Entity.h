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
		EntityType m_Type;
		string m_Name;
		string m_Description;

		Entity* m_Parent;
		list<Entity*> m_Contains;

};

