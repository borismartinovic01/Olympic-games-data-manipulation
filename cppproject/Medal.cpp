#include "Medal.h"

Medal::Medal(string games, string type)
	:games(games)
{
	if (type == "Gold") this->type = Medal::GOLD;
	else if (type == "Silver") this->type = Medal::SILVER;
	else if (type == "Bronze") this->type = Medal::BRONZE;
	else {
		this->type = Medal::GOLD;
	}
}

string Medal::getGames()
{
	return games;
}
