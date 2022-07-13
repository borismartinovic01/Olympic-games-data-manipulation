#ifndef _sport_h
#define _sport_h
#include "Discipline.h"
#include <unordered_set>
#include <string>
using namespace std;

class Sport
{
private:
	unordered_set<string> disciplines;
	string name;
public:
	Sport(string name)
		:name(name){}

	string getName();
	void addDiscipline(string disciplineName);
	bool disciplineExists(string disciplineName);
	
	auto begin()const { return disciplines.begin(); }
	auto end()const { return disciplines.end(); }

	Sport(const Sport&) = delete;
	void operator=(const Sport&) = delete;
};

#endif // !_sport_h


