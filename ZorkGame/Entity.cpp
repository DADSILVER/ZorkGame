#include "Entity.h"
#include <iostream>

// ----------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* parent) :
	name(name), description(description), parent(parent)
{
	type = ENTITY;

	if (parent != NULL)
		parent->contains.push_back(this);
}

// ----------------------------------------------------
Entity::~Entity()
{}

// ----------------------------------------------------
void Entity::Tick()
{}

