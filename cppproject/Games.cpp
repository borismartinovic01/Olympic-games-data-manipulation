#include "Games.h"

string Games::getId()
{
    return id;
}

void Games::addCompetitor(int competitorId)
{
    competitors.insert(competitorId);
}

bool Games::competitorExists(int competitorId)
{
    return competitors.count(competitorId);
}

int Games::getYear()
{
    return year;
}

string Games::getType()
{
    return type;
}

string Games::getCity()
{
    return city;
}
