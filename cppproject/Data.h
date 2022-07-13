#ifndef _data_h
#define _data_h
using namespace std;
#include "Country.h"
#include "Games.h"
#include "Sport.h"
#include "Athlete.h"
#include "Team.h"
#include "Discipline.h"
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>
class Data
{
private:
	unordered_map<string, Games*> gamess;
	unordered_map<string, Country*> countries;
	unordered_map<string, Sport*> sports;
	unordered_map<int, Competitor*> competitors;
	unordered_map<string, Discipline*> disciplines;
	unordered_map<string, Medal*> medals;
	static Data* instance;
	Data(){}
public:
	Data(const Data&) = delete;
	void operator=(const Data&) = delete;
	static Data* getInstance();
	~Data();

	void addGames(string gamesName, string city);
	void addCountry(string countryName);
	void addSport(string sportName);
	int addTeam();
	void addAthlete(int id, string name, char gender, int age, int height, int weight);
	void addDiscipline(string disciplineName, string type);
	void addMedal(string type, string gamesName);
	unordered_map<string, Games*>::iterator getGames(string gamesName);
	unordered_map<string, Discipline*>::iterator getDiscipline(string disciplineName);
	unordered_map<string, Sport*>::iterator getSport(string sportName);
	unordered_map<int, Competitor*>::iterator getCompetitor(int competitorId);
	unordered_map<string, Country*>::iterator getCountry(string countryName);
	int countCompetitors(string country, string year, string type, string sport, string medal);
	int countDisciplines(string country, string year, string type, string sport);
	double getAvgHeight(string country, string year, string type, string sport, string medal);
	double getAvgWeight(string country, string year, string type, string sport, string medal);
	void applyFilters(vector<int>& result, unordered_set<int>& result1, unordered_set<int>& result2, string country, string year, string type, string sport, string medal);
	int countDistinctSports(string countryName);
	vector<string> threeBestCountries(string gamesName);
	void bestCountries();
	void tenYoungest();
	void getPairsCountryAthlete();
	void athletesOnBothGames(string gamesName1, string gamesName2);
	void getTeams(string countryName, string gamesName);
	void getCities();

	int numofDisciplines(string yearSeason);
	double avgHeight(string yearSeason);
	double avgWeight(string yearSeason);
};

#endif // !_data_h



