#include "Sport.h"

string Sport::getName()
{
    return name;
}

void Sport::addDiscipline(string disciplineName)
{
    if(!disciplineName.empty()) disciplines.insert(disciplineName);
}

bool Sport::disciplineExists(string disciplineName)
{
    return disciplines.count(disciplineName);
}
