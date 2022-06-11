#include <iostream>
#include "Entity.h"

// ----------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* parent) :
	M_name(name), M_description(description), M_parent(parent)
{
	M_type = ENTITY;

	if (parent != NULL)
		parent->M_contains.push_back(this);
}

// ----------------------------------------------------
Entity::~Entity()
{}

// ----------------------------------------------------
void Entity::Look() const
{
	cout << M_name << "\n";
	cout << M_description << "\n";
}

// ----------------------------------------------------
void Entity::Tick()
{}

