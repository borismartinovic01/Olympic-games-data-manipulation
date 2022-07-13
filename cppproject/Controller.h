#ifndef _controller_h
#define _controller_h
#include "Data.h"
#include <fstream>
#include <string>
#include <regex>

class Controller
{
private:
	static Controller* instance;
	Data* data;
	int mode;
	Controller()
		:data(data->getInstance()), mode(-1){}
public:
	Controller(const Controller&) = delete;
	void operator=(const Controller&) = delete;
	~Controller();
	static Controller* getInstance();
	void read();
	Data* getData();
	void parse(string fileName1, string fileName2, string year);
	void numOfCompetitors();
	void numOfDisciplines();
	void avgHeight();
	void avgWeight();
	void numOfDistinctSports();
	void threeBestCountries();
	void bestCountries();
	void tenYoungest();
	void getPairsCountryAthlete();
	void athletesOnBothGames();
	void getTeams();
	void getCities();
};

#endif // !_controller_h

