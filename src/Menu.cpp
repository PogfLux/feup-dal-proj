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
        case RELOAD_MENU:
            reloadMenu();
            break;
		case EXIT:
			throw Exit();
	}
}

void UserInterface::mainMenu() {
	std::cout << "COMPANY THAT TRANSPORTS (CTT)\n\n"
				 "1. Optimize couriers\n"
				 "2. Optimize profit\n"
				 "3. Optimize express deliveries\n"
                 "4. Reload Company\n"
                 "0. Exit\n" << std::flush;

	unsigned option = getUnsignedInput("Please insert option: ", 0, 4);

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
        case 4:
            currentMenu = RELOAD_MENU;
            break;

        default:
			errorMessage = "Invalid option...\n";
	}
}

void UserInterface::courierMenu() {

    clearScreen();
    std::tuple<int, int, double> res;

    std::cout << "Optimizing couriers by:\n\n"
                 "1. Weight\n"
                 "2. Volume\n"
                 "3. Both (ratio: weight/volume)\n"
                 "0. Back\n" << std::flush;

    unsigned option = getUnsignedInput("Please insert option: ", 0, 3);

    switch (option) {
        case 0:
            currentMenu = MAIN_MENU;
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

    clearScreen();

	if (std::get<1>(res) != company->get_warehouse_size()) {
		std::cout << "Not all deliveries will be done today! (" << ((float) std::get<1>(res) / company->get_warehouse_size()) * 100 << "%)\n";
	} else {
		std::cout << "All deliveries will be done today!\n";
	}

	std::cout << "Number of trucks used: " << std::get<0>(res) << "\n";
    std::cout << "Finished in: " << std::get<2>(res) << "ms" << std::endl;

    waitForEnter();
    clearScreen();

	currentMenu = MAIN_MENU;
}

void UserInterface::profitMenu() {
    clearScreen();
    auto results = company->bin_packing_profit();
    int num_trucks = std::get<0>(results);
    int profit = std::get<1>(results);
    double time = std::get<2>(results);

    std::cout << "Number of trucks used: " << num_trucks << '\n';
    std::cout << "Profit made: " << profit << '\n';
    std::cout << "Finished in: " << time << " ms" << '\n';

    waitForEnter();
    clearScreen();

    currentMenu = MAIN_MENU;
}

void UserInterface::expressMenu() {
    clearScreen();
    auto results = company->bin_packing_express();
    int delivered = std::get<0>(results);
    double time = std::get<1>(results);

    if (delivered != company->get_warehouse_size()) {
        std::cout << "Not all deliveries will be done today! (" << ((float) delivered / company->get_warehouse_size()) * 100 << "%)\n";
    } else {
        std::cout << "All deliveries will be done today!\n";
    }

    std::cout << "Finished in: " << time << " ms" << '\n';

    waitForEnter();
    clearScreen();

    currentMenu = MAIN_MENU;
}

void UserInterface::reloadMenu() {
    clearScreen();

    std::cout << "Reloading dataset to (# deliveries/# trucks):\n\n"
                 "1. Default (450/50)\n"
                 "2. Deliveries > Trucks (1350/50)\n"
                 "3. Trucks > Deliveries (300/50)\n"
                 "0. Back\n" << std::flush;

    unsigned option = getUnsignedInput("Please insert option: ", 0, 3);

    switch (option) {
        case 0:
            currentMenu = MAIN_MENU;
            break;
        case 1:
            company->reload(DEFAULT);
            break;
        case 2:
            company->reload(DELIVERIES);
            break;
        case 3:
            company->reload(TRUCKS);
            break;
        default:
            errorMessage = "Invalid option...\n";
    }

    clearScreen();

    currentMenu = MAIN_MENU;
}


