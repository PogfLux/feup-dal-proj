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
	std::vector<Delivery> deliveries = *company->get_deliveries();

	std::sort(deliveries.begin(), deliveries.end(), [](Delivery &a, Delivery &b){
		return a.get_weight() > b.get_weight() || a.get_volume() > b.get_volume();
	});

	unsigned int num_trucks = 0, delivered = 0;
	std::vector<std::pair<int, int>> remaining; // weight, volume

	for (auto truck: *company->get_trucks()) {
		remaining.push_back(std::make_pair(0, 0));
	}

	for (int i{0}; i < company->get_warehouse_size(); i++) {
		bool found = false;

		for (int j{0}; j < company->get_garage_size(); j++) {
			int rem_truck_wei = (company->get_truck(j).get_max_weight() + remaining.at(j).first) - deliveries.at(i).get_weight();
			int rem_truck_vol = (company->get_truck(j).get_max_volume() + remaining.at(j).second) - deliveries.at(i).get_volume();
			if (rem_truck_wei >= 0 && rem_truck_vol >= 0) {
				remaining.at(j).first -= company->get_delivery(i).get_weight();
				remaining.at(j).second -= company->get_delivery(i).get_volume();

				found = true;
				delivered++;
				break;
			}
		}

		if (!found) {
			break;
		}
	}

	for (auto truck: remaining) {
		if (truck.first != 0 && truck.second != 0) {
			num_trucks++;
		}
	}


	if (delivered != company->get_warehouse_size()) {
		std::cout << "Not all deliveries will be done today! (" << delivered << "/" << company->get_warehouse_size() << ")\n";
	} else {
		std::cout << "All deliveries will be done today!\n";
	}

	std::cout << "Number of trucks used: " << num_trucks << std::endl;
	currentMenu = MAIN_MENU;
}

void UserInterface::profitMenu() {
	// TODO: WRITE THE ALGORITHM
}

void UserInterface::expressMenu() {
	// TODO: WRITE THE ALGORITHM
}


