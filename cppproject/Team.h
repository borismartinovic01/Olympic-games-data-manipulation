#ifndef _team_h
#define _team_h
#include "Competitor.h"
#include <vector>
#include <string>
#include <iostream>

class Team: public Competitor
{
private:
	vector<int> athleteId;
	static int cnt;
public:
	Team()
		:Competitor(--cnt){}

	Team(const Team&) = delete;
	void operator=(const Team&) = delete;
	auto begin()const { return athleteId.begin(); }
	auto end()const { return athleteId.end(); }

	bool athleteExists(int id);
	int getTeamSize();

	void addAthlete(int id);

	friend ostream& operator<<(ostream& it, const Team& team) {
		for (auto i = team.begin(); i != team.end(); i++) {
			if (i != team.begin()) {
				it << ", ";
			}
			it << (*i);
		}
		return it;
	}
};

#endif // !_team_h
