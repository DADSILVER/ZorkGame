#include <string>
#include <vector>

using namespace std;

namespace globals {  
	bool Same(const string& a, const string& b);
	bool Same(const char* a, const string& b);
	bool Same(const string& a, const char* b);
	int Roll(int min, int max);
	void Tokenize(const string& line, vector<string>& arguments);
}


