#include "Discipline.h"

Discipline::Discipline(string name, string type)
    :name(name)
{
    if (type == "Individual") this->type = Event::INDIVIDUAL;
    else if (type == "Team") this->type = Event::TEAM;
    else {
        this->type = Event::INDIVIDUAL;
    }
}

string Discipline::getName()
{
    return name;
}

string Discipline::getType()
{
    if (type == INDIVIDUAL) return "individual";
    return "team";
}
