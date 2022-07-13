#include "Competitor.h"

Competitor::~Competitor(){}

int Competitor::getId()
{
    return id;
}

void Competitor::addMedals(set<pair<string, string> > medals)
{
    this->medals.insert(medals.begin(), medals.end());
}

void Competitor::addDiscipline(set<pair<string, string> > gamesDis)
{
    this->gamesSet.insert(gamesDis.begin(), gamesDis.end());
}

void Competitor::addCountry(multiset<pair<string, string> > param)
{
    this->countryHash.insert(param.begin(), param.end());
}

set<pair<string, string>>& Competitor::getMedals()
{
    return medals;
}

set<pair<string, string>>& Competitor::getDisciplines()
{
    return gamesSet;
}

multiset<pair<string, string> >& Competitor::getCountries()
{
    return countryHash;
}
