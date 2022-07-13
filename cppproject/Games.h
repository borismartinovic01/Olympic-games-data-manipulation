#ifndef _games_h
#define _games_h
#include "Competitor.h"
#include <unordered_set>
#include <string>
using namespace std;

class Games
{
private:
	unordered_set<int> competitors;
	string city;
	int year;
	string type;
	string id;
public:
	Games(int year, string type, string city)
		:year(year), type(type), city(city), id(to_string(year) + " " + type) {}
	
	string getId();
	void addCompetitor(int competitorId);

	auto begin()const { return competitors.begin(); }
	auto end()const { return competitors.end(); }

	bool competitorExists(int competitorId);
	int getYear();
	string getType();
	string getCity();

	Games(const Games&) = delete;
	void operator=(const Games&) = delete;
};

#endif // !_games_h



