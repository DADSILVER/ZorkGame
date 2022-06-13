#include "Entity.h"

#include <string>
#include <list>
#include <vector>

class Exit;

using namespace std;


class Room :
    public Entity
{
	public:
		Room(const char* name, const char* description);
		~Room();

		void look(const vector<string>& args) const;
		Exit* getExit(const string& direction) const;


public:
};

