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

    std::vector<Truck> trucks = *company->get_trucks();
    std::sort(trucks.begin(), trucks.end(), [] (const Truck& a, const Truck& b) {
       return a.get_cost() < b.get_cost();
    });

    std::vector<Delivery> deliveries = *company->get_deliveries();
    std::sort(deliveries.begin(), deliveries.end(), [] (const Delivery& a, const Delivery& b) {
        return a.get_reward() > b.get_reward();
    });

    unsigned int num_trucks = 0, delivered = 0;
    int profit = 0;

    std::vector<std::pair<int, int>> remaining;

    for (int i = 0; i < company->get_garage_size(); i++) {
        remaining.push_back(std::make_pair(0, 0));
    }

    for (int i = 0; i < company->get_warehouse_size(); i++) {
        bool found = false;

        for (int j = 0; j < company->get_garage_size(); j++) {
            int rem_truck_wei = (trucks.at(j).get_max_weight() + remaining.at(j).first) - deliveries.at(i).get_weight();
            int rem_truck_vol = (trucks.at(j).get_max_volume() + remaining.at(j).second) - deliveries.at(i).get_volume();
            bool isEmpty = (remaining.at(j).first == 0 && remaining.at(j).second == 0);

            if (rem_truck_wei >= 0 && rem_truck_vol >= 0) {
                remaining.at(j).first -= deliveries.at(i).get_weight();
                remaining.at(j).second -= deliveries.at(i).get_volume();
                int reward = deliveries.at(i).get_reward();
                int tran_cost = trucks.at(j).get_cost();

                profit += isEmpty ? reward - tran_cost : reward;

                found = true;
                delivered++;
                break;
            }

        }
    }

    for (auto truck: remaining) {
        if (truck.first != 0 && truck.second != 0) {
            num_trucks++;
        }
    }

    if (delivered != company->get_warehouse_size()) {
        std::cout << "Not all deliveries will be done today! (" << delivered << '/' << company->get_warehouse_size() << ")\n";
    } else {
        std::cout << "All deliveries will be done today!\n";
    }

    std::cout << "Number of trucks used: " << num_trucks << '\n';
    std::cout << "Profit made: " << profit << '\n';

    currentMenu = MAIN_MENU;
}

void UserInterface::expressMenu() {
	// TODO: WRITE THE ALGORITHM
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


