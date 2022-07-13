#ifndef _competitor_h
#define _competitor_h
#include "Medal.h"
#include "Discipline.h"
#include <utility>
#include <set>
#include <unordered_map>
class Competitor
{
private:
	set<pair<string, string> > medals;
	set<pair<string, string> > gamesSet;
	multiset<pair<string, string> > countryHash;
	int id;
public:
	Competitor(int id)
		:id(id){}
	virtual ~Competitor() = 0;
	int getId();
	void addMedals(set<pair<string, string> > medals);
	void addDiscipline(set<pair<string, string> > gamesDis);
	void addCountry(multiset<pair<string, string> > param);
	set<pair<string, string> >& getMedals();
	set<pair<string, string> >& getDisciplines();
	multiset<pair<string, string> >& getCountries();
	Competitor(const Competitor&) = delete;
	void operator=(const Competitor&) = delete;
};

#endif // !_competitor_h



