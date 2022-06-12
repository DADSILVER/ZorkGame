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

void Entity::look() const
{
	cout << m_Name << "\n";
	cout << m_Description << "\n";
}

void Entity::tick()
{}

void Entity::changeParentTo(Entity * newParent)
{
	if (m_Parent != NULL)
		m_Parent->m_Contains.remove(this);

	m_Parent = newParent;

	if (m_Parent != NULL)
		m_Parent->m_Contains.push_back(this);
}

Entity* Entity::find(EntityType type) const
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

Entity* Entity::find(const string& name, EntityType type) const
{
	for (list<Entity*>::const_iterator it = m_Contains.begin(); it != m_Contains.cend(); ++it)
	{
		if ((*it)->m_Type == type && same((*it)->m_Name,name))
		{
			return *it;
		}
	}
	return NULL;
}

