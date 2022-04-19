#include "../include/Menu.h"

unsigned long UserInterface::getUnsignedInput(std::string prompt, unsigned long min, unsigned long max) {
	std::string input;
	unsigned long number;
	bool done = false;

	do {
		input = getStringInput(prompt);

		try {
			number = stoul(input);
			done = true;
		} catch (std::invalid_argument) {
			errorMessage = "Invalid input!\n";
			done = false;
		}
	} while (!done || !inRange(number, min, max));

	return number;
}

double UserInterface::getDoubleInput(std::string prompt, double min, double max) {
	std::string input;
	double number;
	bool done = false;

	do {
		input = getStringInput(prompt);

		try {
			number = stod(input);
			done = true;
		} catch (std::invalid_argument) {
			errorMessage = "Invalid input!\n";
			done = false;
		}
	} while (!done || !inRange(number, min, max));

	return number;
}

std::string UserInterface::getStringInput(std::string prompt) {
	std::cout << errorMessage << prompt;
	errorMessage = "";

	std::string input{};

	std::getline(std::cin, input);
	normalizeInput(input);

	if (std::cin.eof())
		currentMenu = EXIT;

	return input;
}

bool UserInterface::inRange(unsigned long n, unsigned long min,
							unsigned long max) {
	bool b = (n <= max) && (n >= min);

	if (!b)
		errorMessage = "Value outside allowed range!\n";

	return b;
}

bool UserInterface::inRange(double n, double min, double max) {
	bool b = (n <= max) && (n >= min);

	if (!b)
		errorMessage = "Value outside allowed range!\n";

	return b;
}

void UserInterface::show() {
	switch (currentMenu) {
		case MAIN_MENU:
			mainMenu();
			break;
		case COURIER_MENU:
			courierMenu();
			break;
		case PROFIT_MENU:
			profitMenu();
			break;
		case EXPRESS_MENU:
			expressMenu();
			break;
		case EXIT:
			throw Exit();
	}
}

void UserInterface::mainMenu() {
	std::cout << "COMPANY\n\n"
				 "1. Optimize couriers\n"
				 "2. Optimize profit\n"
				 "3. Optimize express deliveries\n"
				 "0. Exit\n" << std::flush;

	unsigned option = getUnsignedInput("Please insert option: ");

	switch (option) {
		case 0:
			currentMenu = EXIT;
			break;
		case 1:
			currentMenu = COURIER_MENU;
			break;
		case 2:
			currentMenu = PROFIT_MENU;
			break;
		case 3:
			currentMenu = EXPRESS_MENU;
			break;
		default:
			errorMessage = "Invalid option...\n";
	}
}

void UserInterface::courierMenu() {

    std::pair<int, int> res;

    std::cout << "Optimizing couriers by:\n\n"
                 "1. Weight\n"
                 "2. Volume\n"
                 "3. Both (ratio: weight/volume)\n"
                 "0. Back\n" << std::flush;

    unsigned option = getUnsignedInput("Please insert option: ");

    switch (option) {
        case 0:
            currentMenu = COURIER_MENU;
            break;
        case 1:
            res = company->bin_packing(WEIGHT);
            break;
        case 2:
            res = company->bin_packing(VOLUME);
            break;
        case 3:
            res = company->bin_packing(BOTH);
            break;
        default:
            errorMessage = "Invalid option...\n";
    }

	if (res.second != company->get_warehouse_size()) {
		std::cout << "Not all deliveries will be done today! (" << res.second << "/" << company->get_warehouse_size() << ")\n";
	} else {
		std::cout << "All deliveries will be done today!\n";
	}

	std::cout << "Number of trucks used: " << res.first << std::endl;
	currentMenu = MAIN_MENU;
}

void UserInterface::profitMenu() {
	// TODO: WRITE THE ALGORITHM
}

void UserInterface::expressMenu() {
	// TODO: WRITE THE ALGORITHM
}


