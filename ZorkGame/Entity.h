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
	PLAYER,
	NPCAlly
};


class Entity
{
	public:
		Entity(const char* name, const char* description, Entity* parent);
		virtual ~Entity();

		virtual void look() const;

		virtual void tick();

		void changeParentTo(Entity* new_parent);
		Entity* find(EntityType type) const;
		Entity* find(const string& name, EntityType type) const;

	public:
		EntityType m_Type;
		string m_Name;
		string m_Description;

		Entity* m_Parent;
		list<Entity*> m_Contains;

};

