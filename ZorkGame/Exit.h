#include <string>
#include "entity.h"

class Room;

using namespace std;


class Exit :
    public Entity
{

public:
	Exit(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way = false);
	~Exit();

	void look() const;
	const string& getNameFrom(const Room* room) const;
	Room* getDestinationFrom(const Room* room) const;

public:
	bool m_OneWay;
	bool m_Closed;
	bool m_Locked;
	string m_OppositeName;
	Room* m_Destination;
	Entity* m_Key;

};

