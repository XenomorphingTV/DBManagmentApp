#include <iostream>
#include "Tables.h"
#include "Clear.h"


// This is the start of our menu
void mainMenu() {
	int menuNum{};
	bool passed{ true };
	do {
		std::cout << "1 - Team List\n";
		std::cout << "2 - Contact List\n";
		std::cout << "3 - Deployments\n";
		std::cout << "4 - Account\n";
		std::cout << "Enter a menu: ";
		std::cin >> menuNum;

		// Using a simple switch case to get our input
		switch (menuNum) {
		case 1:
			printTable();
			break;

		case 2:
			printTable();
			break;

		case 3:
			printTable();
			break;
		case 4:
			// No idea what will be here yet
			break;
		default:
			std::cout << "Invalid input\n";
			clearScreen();
			passed = false;
			break;
		}
	} while (!passed);
}