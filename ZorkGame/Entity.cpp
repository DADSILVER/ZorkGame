#include <iostream>
#include "Entity.h"
#include "globals.h"

Entity::Entity(const char* name, const char* description, Entity* parent) :
	m_Name(name), m_Description(description), m_Parent(parent)
{
	m_Type = ENTITY;

	if (parent != NULL)
		parent->m_Contains.push_back(this);
}

Entity::~Entity()
{}

void Entity::Look(const vector<string>& args) const
{
	cout << m_Name << "\n";
	cout << m_Description << "\n";
}

void Entity::Tick()
{}

void Entity::ChangeParentTo(Entity * newParent)
{
	if (m_Parent != nullptr)
		m_Parent->m_Contains.remove(this);

	m_Parent = newParent;

	if (m_Parent != nullptr)
		m_Parent->m_Contains.push_back(this);
}

Entity* Entity::Find(EntityType type) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it)
	{
		if ((*it)->m_Type == type)
		{
			return *it;
		}
	}
	return NULL;
}

bool Entity::Find(Entity* entity) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it)
	{
		if ((*it) == entity)
		{
						return true;
		}
	}
	return false;
}

Entity* Entity::Find(const string& name, EntityType type) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it)
	{
		if ((*it)->m_Type == type && Same((*it)->m_Name,name))
		{
			return *it;
		}
	}
	return nullptr;
}

void Entity::FindAll(EntityType type, list<Entity*>& listToFill) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it)
	{
		if ((*it)->m_Type == type)
			listToFill.push_back(*it);
	}
}
