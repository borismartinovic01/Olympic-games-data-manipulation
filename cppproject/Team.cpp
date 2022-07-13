#include "Team.h"
int Team::cnt = 0;

bool Team::athleteExists(int id)
{
	return find(athleteId.begin(), athleteId.end(), id) != athleteId.end();
}

int Team::getTeamSize()
{
	return athleteId.size();
}

void Team::addAthlete(int id)
{
	athleteId.push_back(id);
}
