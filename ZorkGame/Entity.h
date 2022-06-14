#pragma once

#include <string>
#include <list>
#include <vector>


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

		virtual void Look(const vector<string>& args) const;

		virtual void Tick();

		void ChangeParentTo(Entity* new_parent);
		Entity* Find(EntityType type) const;
		bool Find(Entity* entity) const;
		Entity* Find(const string& name, EntityType type) const;
		void FindAll(EntityType type, list<Entity*>& list_to_fill) const;

	public:
		EntityType m_Type;
		string m_Name;
		string m_Description;

		Entity* m_Parent;
		list<Entity*> m_Contains;

};

