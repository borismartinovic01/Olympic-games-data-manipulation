#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Controller.h"
using namespace std;

int main() {
	
	int option;
	bool ex = false;
	Controller* controller = Controller::getInstance();
	controller->read();

	while (!ex) {
		cout << "Choose an option: " << "\n";
		cout << "1. Number of competitors" << "\n";
		cout << "2. Number of disciplines" << "\n";
		cout << "3. Average height" << "\n";
		cout << "4. Average weight" << "\n";
		cout << "5. Number of distinct sports where country won at least one medal" << "\n";
		cout << "6. Three best countries" << "\n";
		cout << "7. Best countries" << "\n";
		cout << "8. Ten youngest athletes who won a medal on their first games" << "\n";
		cout << "9. Get pairs country-athlete" << "\n";
		cout << "10. Get athletes who participated in two games" << "\n";
		cout << "11. Get teams for specified country and games" << "\n";
		cout << "12. Get cities" << "\n";
		cout << "0. Exit" << "\n";

		cin >> option;

		switch (option) {
		case 0:
			cout << "Are you sure you want to exit? (1-yes/0-no)\n";
			cin >> option;
			if (option == 1) ex = true;
			break;
		case 1:
			controller->numOfCompetitors();
			break;
		case 2:
			controller->numOfDisciplines();
			break;
		case 3:
			controller->avgHeight();
			break;
		case 4:
			controller->avgWeight();
			break;
		case 5:
			controller->numOfDistinctSports();
			break;
		case 6:
			controller->threeBestCountries();
			break;
		case 7:
			controller->bestCountries();
			break;
		case 8:
			controller->tenYoungest();
			break;
		case 9:
			controller->getPairsCountryAthlete();
			break;
		case 10:
			controller->athletesOnBothGames();
			break;
		case 11:
			controller->getTeams();
			break;
		case 12:
			controller->getCities();
			break;
		default:
			break;
		}
	}
	delete controller;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}