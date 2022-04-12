#include <iostream>
#include "include/Menu.h"

int main() {

	Company company;
	UserInterface ui(&company);

	try {
		while (true) {
			ui.show();
		}
	} catch (Exit) {
		std::cout << "Shutting down..." << std::endl;
	}

    /* for testing purposes */

    std::cout << company.get_garage_size() << '\n';

    for (int i = 0; i < 10; i++) {
        std::cout << company.get_truck(i) << "\n";
    }

    std::cout << "\n\nReading deliveries\n\n";

    std::cout << company.get_warehouse_size() << '\n';

    for (int i = 0; i < 10; i++) {
        std::cout << company.get_delivery(i) << '\n';
    }

    return 0;
}
