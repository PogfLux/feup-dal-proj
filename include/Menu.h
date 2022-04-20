#ifndef DALPROJ_MENU_H
#define DALPROJ_MENU_H

#include "utils.h"
#include "Company.h"

#include <algorithm>
#include <limits>
#include <climits>
#include <tuple>

class UserInterface;

/**
 * @brief the menus the user can interact with
 */
enum Menu {
    /**
     * @brief default starting menu and contains the main options
     */
	MAIN_MENU,

    /**
     * @brief shows optimizations of the amount of couriers
     */
	COURIER_MENU,

    /**
     * @brief shows optimizations of the profits of the company
     */
	PROFIT_MENU,

    /**
     * @brief shows optimizations of the express deliveries
     */
	EXPRESS_MENU,

    /**
     * @brief shows a menu with options to reload the company's data
     */
    RELOAD_MENU,

    /**
     * @brief exits the program
     */
	EXIT
};

/**
 * @brief the interface for the user to interact with, should simply display information
 */
class UserInterface {
private:
	/**
	 * @brief pointer to the company to be displayed
	 */
    Company* company;

public:

    /**
     * @brief creates the user interface
     *
     * @param company pointer to the company being loaded and to be displayed
     */
	UserInterface(Company* company) {
		this->company = company;
	}

    /**
     * @brief the menu to show
     */
	Menu currentMenu = MAIN_MENU;

    /**
     * @brief the error message
     */
	std::string errorMessage;

    /**
     * @brief transforms string input into unsigned integer, creates an error message if it fails
     *
     * @param prompt shown to the user
     * @param min the left bound of the limit (inclusive)
     * @param max the right bound of the limit (inclusive)
     * @return the user input, as an unsigned integer
     */
	unsigned long getUnsignedInput(std::string prompt, unsigned long min = 0,
								   unsigned long max = ULONG_MAX);

    /**
     * @brief gets a line from stdin and normalizes it
     *
     * @param prompt shown to the user
     * @return the user input
     */
	std::string getStringInput(std::string prompt);

    /**
     * @brief checks if an unsigned integer n is inside the limit [min, max]
     *
     * @param n the number to be checked
     * @param min the left bound of the limit
     * @param max the right bound of the limit
     * @return boolean of the logical result of: min <= n <= max
     */
	bool inRange(unsigned long n, unsigned long min, unsigned long max);

    /**
     * @brief executes the function corresponding to the correct current menu
     */
	void show();

    /**
     * @brief displays the main menu
     */
	void mainMenu();

    /**
     * @brief asks for optimization options and displays the optimizations of the amount of couriers,
     *        according to user input
     */
	void courierMenu();

    /**
     * @brief displays the optimizations of the profits of the company
     */
	void profitMenu();

    /**
     * @brief displays the optimizations of the express deliveries
     */
	void expressMenu();

    void reloadMenu();
};


#endif //DALPROJ_MENU_H
