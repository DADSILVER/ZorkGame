#include <iostream>
#include "room.h"
#include "Exit.h"

Exit::Exit(const char* name, const char* oppositeName, const char* description, Room* origin, Room* destination, bool oneWay) :
	Entity(name, description, dynamic_cast<Entity*>(origin)),
	m_Closed(false), m_Locked(false), m_Key(NULL), m_OneWay(oneWay), m_Destination(destination), m_OppositeName(oppositeName)
{
	m_Type = EXIT;

	if (m_OneWay == false)
		destination->m_Contains.push_back(this);
}

Exit::~Exit()
{
}

void Exit::Look(const vector<string>& args) const
{
	cout << m_Name << " to " << m_OppositeName << "\n";
	cout << m_Description << "\n";
}

const string& Exit::GetNameFrom(const Room* room) const
{
	if (room == m_Parent)
		return m_Name;
	if (room == m_Destination)
		return m_OppositeName;

	return m_Name;
}

Room* Exit::GetDestinationFrom(const Room* room) const
{
	if (room == m_Parent)
		return m_Destination;
	if (room == m_Destination)
		return (Room*)m_Parent;

	return NULL;
}
