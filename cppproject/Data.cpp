#include "Data.h"
Data* Data::instance = nullptr;
Data* Data::getInstance()
{
	if (instance == nullptr) {
		instance = new Data();
	}
	return instance;
}

Data::~Data()
{
	for (auto i = gamess.begin(); i != gamess.end(); i++) {
		delete i->second;
	}
	for (auto i = countries.begin(); i != countries.end(); i++) {
		delete i->second;
	}
	for (auto i = sports.begin(); i != sports.end(); i++) {
		delete i->second;
	}
	for (auto i = competitors.begin(); i != competitors.end(); i++) {
		delete i->second;
	}
	for (auto i = disciplines.begin(); i != disciplines.end(); i++) {
		delete i->second;
	}
	for (auto i = medals.begin(); i != medals.end(); i++) {
		
		delete i->second;
	}
}

void Data::addGames(string gamesName, string city)
{
	if (!gamess.count(gamesName)) {
		int year = stoi(gamesName.substr(0, gamesName.find(" ")));
		string gamesType = (gamesName.substr(gamesName.find(" ") + 1));
		gamess.insert(make_pair(gamesName, new Games(year, gamesType, city)));
	}
}

void Data::addCountry(string countryName)
{
	if (!countries.count(countryName)) {
		countries.insert(make_pair(countryName, new Country(countryName)));
	}
}

void Data::addSport(string sportName)
{
	if (!sports.count(sportName)) {
		sports.insert(make_pair(sportName, new Sport(sportName)));
	}
}

int Data::addTeam()
{
	Competitor* newCompetitor = new Team();
	int id = newCompetitor->getId();
	competitors.insert(make_pair(id, newCompetitor));
	return id;
}

void Data::addAthlete(int id, string name, char gender, int age, int height, int weight)
{
	if (!competitors.count(id)) {
		Competitor* newCompetitor = new Athlete(id, name, gender, age, height, weight);
		competitors.insert(make_pair(id, newCompetitor));
	}
}

void Data::addDiscipline(string disciplineName, string type)
{
	if (!disciplines.count(disciplineName)) {
		disciplines.insert(make_pair(disciplineName, new Discipline(disciplineName, type)));
	}
}

void Data::addMedal(string type, string gamesName)
{
	if (!type.empty() && !medals.count(gamesName + type)) {
		medals.insert(make_pair(gamesName + type, new Medal(gamesName, type)));
	}
}

unordered_map<string, Games*>::iterator Data::getGames(string gamesName)
{
	return gamess.find(gamesName);
}

unordered_map<string, Discipline*>::iterator Data::getDiscipline(string disciplineName)
{
	return disciplines.find(disciplineName);
}

unordered_map<string, Sport*>::iterator Data::getSport(string sportName)
{
	return sports.find(sportName);
}

unordered_map<int, Competitor*>::iterator Data::getCompetitor(int competitorId)
{
	return competitors.find(competitorId);
}

unordered_map<string, Country*>::iterator Data::getCountry(string countryName)
{
	return countries.find(countryName);
}

int Data::countCompetitors(string country, string year, string type, string sport, string medal)
{
	vector<int> result;
	unordered_set<int> result1;
	unordered_set<int> result2;
	
	applyFilters(result, result1, result2, country, year, type, sport, medal);
	
	return result.size();
}

int Data::countDisciplines(string country, string year, string type, string sport)
{
	//filtriranje na osnovu medalje nema smisla
	vector<string> result;
	unordered_set<string> result1;
	vector<string> result2;

	for (const auto& tmp : disciplines) {
		result.push_back(tmp.first);
	}

	if (!sport.empty()) { 
		auto it = getSport(sport);
		if (it != sports.end()) {
			auto iter = remove_if(result.begin(), result.end(), [this, it](string id) {

				if (count_if(it->second->begin(), it->second->end(), [id](string currD) {return id == currD; }) == 0) {
					return true;
				}
				return false;
				});
			result.erase(iter, result.end());
		}
	}

	if (!country.empty() && !year.empty()) {
		auto it = getCountry(country);
		if (it != countries.end()) {
			for (auto itc = it->second->begin(); itc != it->second->end(); itc++) {
				auto disPerCmp = getCompetitor(*itc)->second->getDisciplines();
				for (auto itd = disPerCmp.begin(); itd != disPerCmp.end(); itd++) {
					if (itd->first.find(year) != string::npos) {
						result1.insert(itd->second);
					}
				}
			}
		}
	}
	else if (!country.empty()) {
		auto it = getCountry(country);
		if (it != countries.end()) {
			for (auto itc = it->second->begin(); itc != it->second->end(); itc++) {
				auto disPerCmp = getCompetitor(*itc)->second->getMedals();
				for (auto itd = disPerCmp.begin(); itd != disPerCmp.end(); itd++) {
					result1.insert(itd->first);
				}
			}
		}
	}
	else if (!year.empty()) {
		auto it = getGames(year + " Summer");
		if (it != gamess.end()) {
			for (auto itc = it->second->begin(); itc != it->second->end(); itc++) {
				auto disPerCmp = getCompetitor(*itc)->second->getMedals();
				for (auto itd = disPerCmp.begin(); itd != disPerCmp.end(); itd++) {
					result1.insert(itd->first);
				}
			}
		}
		it = getGames(year + " Winter");
		if (it != gamess.end()) {
			for (auto itc = it->second->begin(); itc != it->second->end(); itc++) {
				auto disPerCmp = getCompetitor(*itc)->second->getMedals();
				for (auto itd = disPerCmp.begin(); itd != disPerCmp.end(); itd++) {
					result1.insert(itd->first);
				}
			}
		}
	}
	if (!result1.empty()) {
		for (string element : result1) {
			if (find(result.begin(), result.end(), element) != result.end()) {
				result2.push_back(element);
			}
		}
	}
	else {
		result2.insert(result2.end(), result.begin(), result.end());
	}

	if (!type.empty()) {
		auto iter = remove_if(result2.begin(), result2.end(), [this, type](string id) {
			return getDiscipline(id)->second->getType() != type;
			});
		result2.erase(iter, result2.end());
	}

	return result2.size();
}

double Data::getAvgHeight(string country, string year, string type, string sport, string medal)
{
	vector<int> result;
	unordered_set<int> result1;
	unordered_set<int> result2;
	
	applyFilters(result, result1, result2, country, year, type, sport, medal);

	double sum = 0;
	int cnt = 0;
	for (auto it : result) {
		if (it > 0) {
			Athlete* athlete = (Athlete*)(getCompetitor(it)->second);
			sum += athlete->getHeight();
			cnt += (athlete->getHeight() == 0) ? 0 : 1;
		}
		else {
			Team* team = (Team*)(getCompetitor(it)->second);
			for (auto itc = team->begin(); itc != team->end(); itc++) {
				Athlete* athlete = (Athlete*)(getCompetitor(*itc)->second);
				sum += athlete->getHeight();
				cnt += (athlete->getHeight() == 0) ? 0 : 1;
			}
		}
	}

	return sum/cnt;
}

double Data::getAvgWeight(string country, string year, string type, string sport, string medal)
{
	vector<int> result;
	unordered_set<int> result1;
	unordered_set<int> result2;

	applyFilters(result, result1, result2, country, year, type, sport, medal);

	double sum = 0;
	int cnt = 0;
	for (auto it : result) {
		if (it > 0) {
			Athlete* athlete = (Athlete*)(getCompetitor(it)->second);
			sum += athlete->getWeight();
			cnt += (athlete->getWeight() == 0) ? 0 : 1;
		}
		else {
			Team* team = (Team*)(getCompetitor(it)->second);
			for (auto itc = team->begin(); itc != team->end(); itc++) {
				Athlete* athlete = (Athlete*)(getCompetitor(*itc)->second);
				sum += athlete->getWeight();
				cnt += (athlete->getWeight() == 0) ? 0 : 1;
			}
		}
	}

	return sum / cnt;
}

void Data::applyFilters(vector<int>& result, unordered_set<int>& result1, unordered_set<int>& result2, string country, string year, string type, string sport, string medal)
{
	if (!country.empty()) {
		auto it = getCountry(country);
		if (it != countries.end()) {
			result1.insert(it->second->begin(), it->second->end());
		}
	}
	if (!year.empty()) {
		auto it = getGames(year + " Summer");
		if (it != gamess.end()) {
			result2.insert(it->second->begin(), it->second->end());
		}
		it = getGames(year + " Winter");
		if (it != gamess.end()) {
			result2.insert(it->second->begin(), it->second->end());
		}
	}
	if (!result1.empty() && !result2.empty()) {
		for (int element : result1) {
			if (result2.count(element) > 0) {
				result.push_back(element);
			}
		}
	}
	else if (!result1.empty()) {
		result.insert(result.end(), result1.begin(), result1.end());
	}
	else if (!result2.empty()) {
		result.insert(result.end(), result2.begin(), result2.end());
	}

	if (result.empty() && country.empty() && year.empty()) {
		for (const auto& tmp : competitors) {
			if (tmp.second->getMedals().count({ "","" }) != 1) {
				result.push_back(tmp.first);
			}
		}
	}
	if (medal != "0") {
		auto iter = remove_if(result.begin(), result.end(), [this, medal](int id) {
			auto itm = getCompetitor(id)->second->getMedals();
			if (count_if(itm.begin(), itm.end(), [medal](pair<string, string> tmp) {
				if (medal == "none") return tmp.second == "";
				else return tmp.second.find(medal) != string::npos;
				})) {
				return false;
			}
			return true;
			});
		result.erase(iter, result.end());
	}
	if (!type.empty()) {
		auto iter = remove_if(result.begin(), result.end(), [this, type](int id) {
			auto itm = getCompetitor(id)->second->getMedals();
			if (count_if(itm.begin(), itm.end(), [this, type](pair<string, string> tmp) { 
				if (tmp.first.empty()) return false;
				return getDiscipline(tmp.first)->second->getType() == type; 
				})) {
				return false;
			}
			return true;
			});
		result.erase(iter, result.end());
	}
	if (!sport.empty()) {
		auto isp = getSport(sport);
		if (isp != sports.end()) {
			Sport* sp = isp->second;
			auto iter = remove_if(result.begin(), result.end(), [this, sp](int id) {
				auto itm = getCompetitor(id)->second->getMedals();
				if (count_if(itm.begin(), itm.end(), [this, sp](pair<string, string> tmp) {
					if (tmp.first.empty()) return false;
					return sp->disciplineExists(getDiscipline(tmp.first)->second->getName()); 
					})) {
					return false;
				}
				return true;
				});
			result.erase(iter, result.end());
		}
	}
}

int Data::countDistinctSports(string countryName)
{
	int cnt = 0;
	auto it = getCountry(countryName);
	if (it == countries.end()) return cnt;
	unordered_set<string> result;
	for (auto comp : competitors) {
		auto itm = getCompetitor(comp.first)->second->getCountries();
		for (auto iter = itm.begin(); iter != itm.end(); iter++) {
			if (iter->first != countryName) continue;
			auto itmed = getCompetitor(comp.first)->second->getMedals();
			for (auto iterr = itmed.begin(); iterr != itmed.end(); iterr++) {
				if (iterr->second == iter->second) {
					for (auto its : sports) {
						if (its.second->disciplineExists(iterr->first)) {
							result.insert(its.first);
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	
	return result.size();
}

vector<string> Data::threeBestCountries(string gamesName)
{
	map<string, vector<int> > result; 
	vector<string> retval;
	auto it = getGames(gamesName);
	if (it == gamess.end()) {
		cout << "Specified games don't exist.\n";
		return retval;
	}
	unordered_set<string> countryListTmp;
	for (auto comp : competitors) {
		countryListTmp.clear();
		auto itc = getCompetitor(comp.first)->second->getCountries();
		
		for (auto iter = itc.begin(); iter != itc.end(); iter++) {
			countryListTmp.insert(iter->first);
		}
		for (auto iter = countryListTmp.begin(); iter != countryListTmp.end(); iter++) {//iteriranje kroz drzave
			int bronze = count_if(itc.begin(), itc.end(), [gamesName, iter](pair<string, string> tmp) {
				return tmp.first.find(*iter)!=string::npos && tmp.second.find(gamesName + "Bronze") != string::npos;
				});
			int silver = count_if(itc.begin(), itc.end(), [gamesName, iter](pair<string, string> tmp) {
				return tmp.first.find(*iter) != string::npos && tmp.second.find(gamesName + "Silver") != string::npos;
				});
			int gold = count_if(itc.begin(), itc.end(), [gamesName, iter](pair<string, string> tmp) {
				return tmp.first.find(*iter) != string::npos && tmp.second.find(gamesName + "Gold") != string::npos;
				});

			auto it = result.find(*iter);
			if (it == result.end()) {
				vector<int> vc{ gold, silver, bronze };
				result.insert(make_pair(*iter, vc));
			}
			else {
				it->second[0] += gold;
				it->second[1] += silver;
				it->second[2] += bronze;
			}
		}
	}
	
	vector<pair<string, vector<int> > > vc(result.begin(), result.end());

 	sort(vc.begin(), vc.end(), [](pair<string, vector<int> >& a, pair<string, vector<int> >& b)
	{
			if (a.second[0] > b.second[0]) return true;
			else if (a.second[0] < b.second[0]) return false;
			else if (a.second[1] > b.second[1]) return true;
			else if (a.second[1] < b.second[1]) return false;
			else if (a.second[2] > b.second[2]) return true;
			else if (a.second[2] < b.second[2]) return false;
			else return true;
		});
	
	int cnt = 0;
	for (auto it = vc.begin(); it != vc.end() && cnt < 3; it++, cnt++) {
		retval.push_back(it->first);
	}
	return retval;
}

void Data::bestCountries()
{
	unordered_set<string> result;
	vector<string> vc;
	for (auto it : gamess) {
		vc = threeBestCountries(it.first);
		result.insert(vc[0]);
	}
	cout << "Best countries: \n";
	for (auto it : result) cout << it << "\n";
}

void Data::tenYoungest()
{
	vector<pair<int, int> > vc;//athlete i age
	unordered_set<int> athletes;
	int tYear = 0;
	string tGames;
	unordered_map<int, int> helper;
	for (auto it : competitors) {
		if (it.first > 0) {
			tYear = 0;
			tGames.clear();
			for (auto ig : gamess) {
				if ((tGames.empty() || ig.second->getYear() < tYear || (ig.second->getYear() == tYear && ig.second->getType() == "Winter")) && ig.second->competitorExists(it.first)) {
					tYear = ig.second->getYear();
					tGames = ig.second->getId();
				}
			}
			if (tYear == 0) continue;
			Athlete* ic = (Athlete*)(getCompetitor(it.first)->second);
			auto im = ic->getMedals();
			if (find_if(im.begin(), im.end(), [tGames](const pair<string, string>& tmp) { return tmp.second.find(tGames) != string::npos; }) != im.end()) {
				if (ic->getAge() != 0) {
					auto ip = helper.find(it.first);
					if (ip == helper.end()) {
						vc.push_back(make_pair(it.first, ic->getAge()));
						athletes.insert(it.first);
					}
					else if (ip->second > tYear) {
						ip->second = tYear;
					}
					else if (athletes.find(it.first) == athletes.end()) {
						vc.push_back(make_pair(it.first, ic->getAge()));
						athletes.insert(it.first);
					}
				}
			}
			else {
				auto ip = helper.find(it.first);
				auto ik = athletes.find(it.first);
				if (ip != helper.end() && ik != athletes.end() && ip->second > tYear) {
					athletes.erase(ip->first);
				}
			}
			helper.insert(make_pair(it.first, tYear));
		}
		else if(it.first < 0){
			Team* team = (Team*)(getCompetitor(it.first)->second);
			for (auto ic = team->begin(); ic != team->end(); ic++) {
					tYear = 0;
					tGames.clear();
					for (auto ig : gamess) {
						if ((tGames.empty() || ig.second->getYear() < tYear || (ig.second->getYear() == tYear && ig.second->getType() == "Winter")) && ig.second->competitorExists(it.first)) {
							tYear = ig.second->getYear();
							tGames = ig.second->getId();
						}
					}
					if (tYear == 0) continue;
					Athlete* ia = (Athlete*)(getCompetitor(*ic)->second);
					auto im = team->getMedals();
					if (find_if(im.begin(), im.end(), [tGames](const pair<string, string>& tmp) { return tmp.second.find(tGames) != string::npos; }) != im.end()) {
						if (ia->getAge()!=0) {
							auto ip = helper.find(*ic);
							if (ip == helper.end()) {
								vc.push_back(make_pair(*ic, ia->getAge()));
								athletes.insert(*ic);
							}
							else if (ip->second > tYear) {
								ip->second = tYear;
							}
							else if (athletes.find(*ic) == athletes.end()) {
								vc.push_back(make_pair(*ic, ia->getAge()));
								athletes.insert(*ic);
							}
						}
					}
					else {
						auto ip = helper.find(*ic);
						auto ik = athletes.find(*ic);
						if (ip != helper.end() && ik != athletes.end() && ip->second > tYear) {
							athletes.erase(ip->first);
						}
					}
					helper.insert(make_pair(*ic, tYear));
			}
		}
	}
	sort(vc.begin(), vc.end(), [](pair<int, int>& tmp1, pair<int, int>& tmp2) { return tmp1.second < tmp2.second; });

	cout << "Ten youngest athletes who won a medal on their first games: " << "\n";
	int cnt = 0;
	for (auto it = vc.begin(); it != vc.end() && cnt < 10; it++) {
		if (athletes.count(it->first)) {
			cout << it->first << " " << it->second << "\n";
			cnt++;
		}
	}
}

void Data::getPairsCountryAthlete()
{
	vector<pair<string, int> > result;
	unordered_set<int> athletes;
	for (auto cnt : countries) {
		for (auto itc = cnt.second->begin(); itc != cnt.second->end(); itc++) {
			if ((*itc) > 0) {//&& !athletes.count(*itc)
				auto itm = getCompetitor(*itc)->second->getCountries();
				if (find_if(itm.begin(), itm.end(), [cnt](const pair<string, string>& tmp) { return tmp.first==cnt.first; }) != itm.end()
					&& find_if(cnt.second->begin(), cnt.second->end(), [this, itc, cnt](int id) {
						if (id >= 0) return false;
						Team* team = (Team*)(getCompetitor(id)->second);
						if (!(getCountry(cnt.first)->second->competitorExists(id))) return false;
						return team->athleteExists(*itc) && !(team->getMedals().begin()->second.empty());
						}) != cnt.second->end()) {
					result.push_back(make_pair(cnt.first, *itc));
				}
			}
		}
	}

	for (auto it : result) cout << it.first << " - " << it.second << "\n";
}

void Data::athletesOnBothGames(string gamesName1, string gamesName2)
{
	auto it1 = getGames(gamesName1);
	if (it1 == gamess.end()) return;
	auto it2 = getGames(gamesName2);
	if (it2 == gamess.end()) return;
	auto ig1 = it1->second;
	auto ig2 = it2->second;
	unordered_set<int> st; 
	unordered_set<int> st2;

	for (auto itc = ig1->begin(); itc != ig1->end(); itc++) {
		if ((*itc) > 0) st.insert(*itc);
		else {
			Team* team = (Team*)(getCompetitor(*itc)->second);
			st.insert(team->begin(), team->end());
		}
	}

	for (auto itc = ig2->begin(); itc != ig2->end(); itc++) {
		if ((*itc) > 0) st2.insert(*itc);
		else {
			Team* team = (Team*)(getCompetitor(*itc)->second);
			st2.insert(team->begin(), team->end());
		}
	}

	cout << "Athletes who appeared on both games: " << "\n";
	for (int tmp: st) {
		if (st2.count(tmp)) cout << tmp << "\n";
	}
}

void Data::getTeams(string countryName, string gamesName)
{
	auto ic = getCountry(countryName);
	if (ic == countries.end()) return;
	auto ig = getGames(gamesName);
	if (ig == gamess.end()) return;

	unordered_set<int> teams(ic->second->begin(), ic->second->end());
	vector<int> vc;

	Games* games = ig->second;
	for (auto it = games->begin(); it != games->end(); it++) {
		if ((*it)<0 && teams.count(*it)) vc.push_back(*it);
	}

	sort(vc.begin(), vc.end(), [this](int& id1, int& id2) {
		Team* t1 = (Team*)(getCompetitor(id1)->second);
		Team* t2 = (Team*)(getCompetitor(id2)->second);
		if (t1->getTeamSize() > t2->getTeamSize()) return true;
		else if (t1->getTeamSize() == t2->getTeamSize() && t1->getMedals().begin()->first < t2->getMedals().begin()->first) return true;
		else return false;
		});

	cout << "Teams: " << "\n";
	for (auto it : vc) {
		Team* team = (Team*)(getCompetitor(it)->second);
		cout << (*team) << "\n";
	}
}

void Data::getCities()
{
	cout << "Cities: \n";
	unordered_set<string> cities;
	for (auto it : gamess) cities.insert(it.second->getCity());
	for (auto it : cities) {
		cout << it << "\n";
	}
}

int Data::numofDisciplines(string yearSeason)
{
	unordered_set<string> result1;

	auto it = getGames(yearSeason);
	if (it == gamess.end()) return 0;

	for (auto itc = it->second->begin(); itc != it->second->end(); itc++) {
		auto disPerCmp = getCompetitor(*itc)->second->getMedals();
		for (auto itd = disPerCmp.begin(); itd != disPerCmp.end(); itd++) {
			result1.insert(itd->first);
		}
	}
	return result1.size();
}

double Data::avgHeight(string yearSeason)
{
	unordered_set<int> result;
	auto it = getGames(yearSeason);

	if (it == gamess.end()) return 0.0;
	result.insert(it->second->begin(), it->second->end());

	double sum = 0;
	int cnt = 0;
	for (auto it : result) {
		if (it > 0) {
			Athlete* athlete = (Athlete*)(getCompetitor(it)->second);
			sum += athlete->getHeight();
			cnt += (athlete->getHeight() == 0) ? 0 : 1;
		}
		else {
			Team* team = (Team*)(getCompetitor(it)->second);
			for (auto itc = team->begin(); itc != team->end(); itc++) {
				Athlete* athlete = (Athlete*)(getCompetitor(*itc)->second);
				sum += athlete->getHeight();
				cnt += (athlete->getHeight() == 0) ? 0 : 1;
			}
		}
	}
	return sum / cnt;
}

double Data::avgWeight(string yearSeason)
{
	unordered_set<int> result;
	auto it = getGames(yearSeason);

	if (it == gamess.end()) return 0.0;
	result.insert(it->second->begin(), it->second->end());

	double sum = 0;
	int cnt = 0;
	for (auto it : result) {
		if (it > 0) {
			Athlete* athlete = (Athlete*)(getCompetitor(it)->second);
			sum += athlete->getWeight();
			cnt += (athlete->getWeight() == 0) ? 0 : 1;
		}
		else {
			Team* team = (Team*)(getCompetitor(it)->second);
			for (auto itc = team->begin(); itc != team->end(); itc++) {
				Athlete* athlete = (Athlete*)(getCompetitor(*itc)->second);
				sum += athlete->getWeight();
				cnt += (athlete->getWeight() == 0) ? 0 : 1;
			}
		}
	}
	return sum / cnt;
}