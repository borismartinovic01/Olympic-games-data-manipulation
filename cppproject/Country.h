#ifndef _country_h
#define _country_h
#include "Competitor.h"
#include <unordered_set>
#include <string>
using namespace std;
class Country
{
private:
	unordered_set<int> competitors;
	string name;
public:
	Country(string name)
		:name(name){}
	
	string getName();
	void addCompetitor(int competitor);
	unordered_set<int>& getCompetitors();

	auto begin()const { return competitors.begin(); }
	auto end()const { return competitors.end(); }

	bool competitorExists(int competitorId);

	Country(const Country&) = delete;
	void operator=(const Country&) = delete;
};

#endif // !_country_h



