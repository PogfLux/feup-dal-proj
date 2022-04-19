#ifndef DALPROJ_MENU_H
#define DALPROJ_MENU_H

#include "utils.h"
#include "Company.h"

#include <algorithm>
#include <limits>
#include <climits>
#include <tuple>

class UserInterface;

enum Menu {
	MAIN_MENU,
	COURIER_MENU,
	PROFIT_MENU,
	EXPRESS_MENU,
	EXIT
};

class UserInterface {
	Company* company;
public:

	explicit UserInterface(Company* company) {
		this->company = company;
	}

	Menu currentMenu = MAIN_MENU;

	std::string errorMessage;

	unsigned long getUnsignedInput(std::string prompt, unsigned long min = 0,
								   unsigned long max = ULONG_MAX);

	double getDoubleInput(std::string prompt,
						  double min = std::numeric_limits<double>::min(),
						  double max = std::numeric_limits<double>::max());

	std::string getStringInput(std::string prompt);

	bool inRange(unsigned long n, unsigned long min, unsigned long max);

	bool inRange(double n, double min, double max);

	void show();

	void mainMenu();

	void courierMenu();

	void profitMenu();

	void expressMenu();
};


#endif //DALPROJ_MENU_H
