#ifndef _discipline_h
#define _discipline_h
#include <string>
using namespace std;

class Discipline
{
private:
	enum Event { INDIVIDUAL, TEAM };
	string name;
	Event type;
public:
	Discipline(string name, string type);
	string getName();
	string getType();
	Discipline(const Discipline&) = delete;
	void operator=(const Discipline&) = delete;
};

#endif // !_discipline_h



