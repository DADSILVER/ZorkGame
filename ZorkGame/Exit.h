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

	void Look() const;

public:
	bool M_oneWay;
	bool M_closed;
	bool M_locked;
	string M_oppositeName;
	Room* M_destination;
	Entity* M_key;

};

