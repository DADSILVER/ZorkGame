#include <vector>
#include "globals.h"


bool globals::Same(const string& a, const string& b)
{
    return _stricmp(a.c_str(), b.c_str()) == 0;
}

bool globals::Same(const char* a, const string& b)
{
	return _stricmp(a, b.c_str()) == 0;
}

bool globals::Same(const string& a, const char* b)
{
	return _stricmp(a.c_str(), b) == 0;
}

int globals::Roll(int min, int max)
{
	if (max == 0)
	{
		return 0;
	}
	if (min>max)
	{
		min = max;
	}

	return rand() % max + min;
}

void globals::Tokenize(const string& line, vector<string>& arguments)
{
	const char* str = line.c_str();

	do
	{
		const char* begin = str;

		while (*str != ' ' && *str)
			str++;

		arguments.push_back(string(begin, str));
	} while (0 != *str++);
}
