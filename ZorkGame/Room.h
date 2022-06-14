#include "Entity.h"

#include <string>
#include <list>
#include <vector>

class Exit;

using namespace std;

enum class RoomType
{
	NORMAL,
	OCEAN
};

class Room :
    public Entity
{
	public:
		Room(const char* name, const char* description, RoomType roomType);
		~Room();

		void Look(const vector<string>& args) const override;
		Exit* GetExit(const string& direction) const;


public:
	RoomType m_RoomType;
};

