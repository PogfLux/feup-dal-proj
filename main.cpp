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
        clearScreen();
		std::cout << "Shutting down..." << std::endl;
	}

    return 0;
}
