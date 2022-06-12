#include <iostream>
#include "Entity.h"

Entity::Entity(const char* name, const char* description, Entity* parent) :
	m_Name(name), m_Description(description), m_Parent(parent)
{
	m_Type = ENTITY;

	if (parent != NULL)
		parent->m_Contains.push_back(this);
}

Entity::~Entity()
{}

void Entity::Look() const
{
	cout << m_Name << "\n";
	cout << m_Description << "\n";
}

void Entity::Tick()
{}

