#ifndef _athlete_h
#define _athlete_h
#include "Competitor.h"

class Athlete: public Competitor
{
private:
	string name;
	char gender;
	int age;
	int height;
	int weight;
public:
	Athlete(int id, string name, char gender, int age = 0, int height = 0, int weight = 0)
		:Competitor(id), name(name), gender(gender), age(age), height(height), weight(weight){}


	int getHeight();
	int getWeight();
	int getAge();
	Athlete(const Athlete&) = delete;
	void operator=(const Athlete&) = delete;
};

#endif // !_athlete_h