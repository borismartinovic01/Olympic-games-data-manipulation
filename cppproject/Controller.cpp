#include "Controller.h"
#include <iostream>
Controller* Controller::instance = nullptr;

Controller::~Controller()
{
	delete data;
}

Controller* Controller::getInstance() {
	if (instance == nullptr) {
		instance = new Controller();
	}
	return instance;
}

void Controller::read()
{
	cout << "Enter mode in which data should be read\n0. Read all data\n1. Read data for specified year\nOption: ";
	cin >> mode;
	if (mode == 0) parse("events.txt", "athletes.txt", "");
	else if (mode == 1) {
		string year;
		cout << "Enter year: ";
		cin >> year;
		parse("events.txt", "athletes.txt", year);
	}
	else {
		return;
	}
}

Data* Controller::getData()
{
	return data;
}

void Controller::parse(string fileName1, string fileName2, string year)
{
	ifstream file(fileName1);
	string line;
	string pattern = "(" + year + "[^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)";
	regex rx(pattern);
	Controller* controller = Controller::getInstance();
	Data* data = controller->getData();
	unordered_map<int, set<pair<string, string> > > newAthletes;
	unordered_map<int, set<pair<string, string> > > gamesDisAth;
	unordered_map<int, multiset<pair<string, string> > > discHash;
	while (getline(file, line)) {
		smatch result;
		if (regex_match(line, result, rx)) {

			string games = result.str(1);
			string city = result.str(2);
			string sport = result.str(3);
			string discipline = result.str(4);
			string type = result.str(5);
			string country = result.str(6);
			string ids = result.str(7);
			string medal = result.str(8);
			
			data->addDiscipline(discipline, type);
			data->addCountry(country);
			data->addGames(games, city);
			data->addSport(sport);
			data->getSport(sport)->second->addDiscipline(discipline);
			data->addMedal(games, medal);
			
			if (ids[0] != '[') {
				auto it = newAthletes.find(stoi(ids));
				data->getGames(games)->second->addCompetitor(stoi(ids));
				data->getCountry(country)->second->addCompetitor(stoi(ids));
				if (it == newAthletes.end()) {
					newAthletes.insert(make_pair(stoi(ids), std::initializer_list<std::pair<string, string> >{make_pair(discipline, (!medal.empty()) ? games + medal : "")}));
				}
				else {
					it->second.insert(make_pair(discipline, (!medal.empty()) ? games + medal : ""));
					
				}
				auto itd = gamesDisAth.find(stoi(ids));
				if (itd == gamesDisAth.end()) {

					gamesDisAth.insert(make_pair(stoi(ids), std::initializer_list<std::pair<string, string> >{make_pair(games, discipline)}));
				}
				else {
					itd->second.insert(make_pair(games, discipline));
				}
				if (!medal.empty()) {
					auto ith = discHash.find(stoi(ids));
					if (ith == discHash.end()) {

						discHash.insert(make_pair(stoi(ids), std::initializer_list<std::pair<string, string> >{make_pair(country, games+medal)}));
					}
					else {
						ith->second.insert(make_pair(country, games+medal));
					}
				}
			}
			else {
				int competitorId = data->addTeam();
				auto it = data->getCompetitor(competitorId);
				Team* team = (Team*)(it->second);
				team->addMedals(std::initializer_list<std::pair<string, string> >{make_pair(discipline, (!medal.empty()) ? games+medal : "")});
				team->addDiscipline(std::initializer_list<std::pair<string, string> >{make_pair(games, discipline)});
				team->addCountry(std::initializer_list<std::pair<string, string> >{make_pair(country, games+medal)});
				data->getGames(games)->second->addCompetitor(competitorId);
				data->getCountry(country)->second->addCompetitor(competitorId);

				ids.pop_back();
				ids.erase(0, 1);
				regex rxi("'([^']+)',? ?");
				sregex_iterator begin(ids.begin(), ids.end(), rxi);
				sregex_iterator end;
				
				while (begin != end) {
					smatch sm = *begin;
					int id = stoi(sm.str(1));
					team->addAthlete(id);
					//hesiranje atlete
					auto it = newAthletes.find(id);
					if (it == newAthletes.end()) {
						newAthletes.insert(make_pair(id, std::initializer_list<std::pair<string, string> >{make_pair("", "")}));
					}
					begin++;
				}
			}
		}
	}
	file.close();
	ifstream file2(fileName2);
	string pattern2 = "([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)";
	regex rx2(pattern2);
	int cnt = newAthletes.size();
	while (getline(file2, line)) {
		smatch result;
		if (regex_match(line, result, rx2)) {
			int id = stoi(result.str(1));
			auto it = newAthletes.find(id);
			if (it == newAthletes.end()) continue;
			string name = result.str(2);
			char gender = (result.str(3))[0];
			int age = (result.str(4) == "NA") ? 0 : stoi(result.str(4));
			int height = (result.str(5) == "NA") ? 0 : stoi(result.str(5));
			int weight = (result.str(6) == "NA") ? 0 : stoi(result.str(6));
			data->addAthlete(id, name, gender, age, height, weight);
			auto ic = data->getCompetitor(id);
			Competitor* tmp = ic->second;
			tmp->addMedals(it->second);
			auto itd = gamesDisAth.find(id);
			if (itd != gamesDisAth.end()) tmp->addDiscipline(itd->second);
			auto ite = discHash.find(id);
			if (ite != discHash.end()) tmp->addCountry(ite->second);
			if (--cnt <= 0) break;
		}
	}

	file2.close();
}

void Controller::numOfCompetitors()
{
	string sport, country, eventType, medal, year;
	cout << "Filters:\nSport: ";
	cin.ignore();
	getline(cin, sport);
	cout << "Country: ";
	getline(cin, country);
	cout << "Year: ";
	getline(cin, year);
	cout << "Event type: ";
	getline(cin, eventType);
	cout << "Medal: ";//none
	getline(cin, medal);
	if (country == "0") country.clear();
	if (sport == "0") sport.clear();
	if (year == "0") year.clear();
	if (eventType == "0") eventType.clear();
	else if (medal == "0") medal.clear();
	
	cout << "Number of competitors: "<< data->countCompetitors(country, year, eventType, sport, medal) << "\n";
}

void Controller::numOfDisciplines()
{
	string sport, country, eventType, year;
	cout << "Filters:\nSport: ";
	cin.ignore();
	getline(cin, sport);
	cout << "Country: ";
	getline(cin, country);
	cout << "Year: ";
	getline(cin, year);
	cout << "Event type: ";
	getline(cin, eventType);
	if (country == "0") country.clear();
	if (sport == "0") sport.clear();
	if (year == "0") year.clear();
	if (eventType == "0") eventType.clear();

	cout << "Number of disciplines: " << data->countDisciplines(country, year, eventType, sport) << "\n";
}

void Controller::avgHeight()
{
	string sport, country, eventType, medal, year;
	cout << "Filters:\nSport: ";
	cin.ignore();
	getline(cin, sport);
	cout << "Country: ";
	getline(cin, country);
	cout << "Year: ";
	getline(cin, year);
	cout << "Event type: ";
	getline(cin, eventType);
	cout << "Medal: ";//none
	getline(cin, medal);
	if (country == "0") country.clear();
	if (sport == "0") sport.clear();
	if (year == "0") year.clear();
	if (eventType == "0") eventType.clear();
	else if (medal == "0") medal.clear();

	cout << "Average height: " << data->getAvgHeight(country, year, eventType, sport, medal) << "\n";
}

void Controller::avgWeight()
{
	string sport, country, eventType, medal, year;
	cout << "Filters:\nSport: ";
	cin.ignore();
	getline(cin, sport);
	cout << "Country: ";
	getline(cin, country);
	cout << "Year: ";
	getline(cin, year);
	cout << "Event type: ";
	getline(cin, eventType);
	cout << "Medal: ";//none
	getline(cin, medal);
	if (country == "0") country.clear();
	if (sport == "0") sport.clear();
	if (year == "0") year.clear();
	if (eventType == "0") eventType.clear();
	else if (medal == "0") medal.clear();

	cout << "Average weight: " << data->getAvgWeight(country, year, eventType, sport, medal) << "\n";
}

void Controller::numOfDistinctSports()
{
	string countryName;
	cin.ignore();
	cout << "Country: ";
	getline(cin, countryName);

	cout << "Number of distinct sports where " << countryName << " won at least one medal: " << data->countDistinctSports(countryName) << "\n";
}

void Controller::threeBestCountries()
{
	string year, season;
	cin.ignore();
	cout << "Year: ";
	getline(cin, year);
	cout << "Season: ";
	getline(cin, season);
	vector<string> result = data->threeBestCountries(year + " " + season);
	cout << "Three best countries: \n";
	for (auto it : result) cout << it << "\n";
}

void Controller::bestCountries()
{
	data->bestCountries();
}

void Controller::tenYoungest()
{
	data->tenYoungest();
}

void Controller::getPairsCountryAthlete()
{
	data->getPairsCountryAthlete();
}

void Controller::athletesOnBothGames()
{
	string gamesName1, gamesName2;
	cin.ignore();
	cout << "Games 1: ";
	getline(cin, gamesName1);
	cout << "Games 2: ";
	getline(cin, gamesName2);
	data->athletesOnBothGames(gamesName1, gamesName2);
}

void Controller::getTeams()
{
	string countryName, gamesName;
	cin.ignore();
	cout << "Country: ";
	getline(cin, countryName);
	cout << "Games: ";
	getline(cin, gamesName);
	data->getTeams(countryName, gamesName);
}

void Controller::getCities()
{
	data->getCities();
}

