#ifndef _medal_h
#define _medal_h
#include "Games.h"
#include <string>
using namespace std;

class Medal
{
private:
	enum Type { GOLD, SILVER, BRONZE };
	Type type;
	string games;
public:
	Medal(string games, string type);

	string getGames();

	Medal(const Medal&) = delete;
	void operator=(const Medal&) = delete;
};

#endif // !_medal_h



