#include "Country.h"

string Country::getName()
{
    return name;
}

void Country::addCompetitor(int competitor)
{
    competitors.insert(competitor);
}

unordered_set<int>& Country::getCompetitors()
{
    return competitors;
}

bool Country::competitorExists(int competitorId)
{
    return competitors.count(competitorId);
}
