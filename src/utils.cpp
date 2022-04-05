#include "../include/utils.h"

void clearScreen() {std::cout << std::string(500, '\n') << std::endl;};

void clearInput() {std::cin.clear(); std::cin.ignore(MAX_CHARS_IGNORE, '\n');};

void waitForEnter(std::string prompt) {
    if (std::cin.good()) std::cout << prompt << std::endl;
    if (std::cin.peek() == '\n') std::cin.ignore(MAX_CHARS_IGNORE, '\n');
}

std::vector<std::string> split(std::string str, char sep) {
    std::string temp;
    std::vector<std::string> final;

    for (auto i : str) {
        if (i == sep) {
            final.push_back(temp);
            temp = "";
        } else {
            temp += i;
        }
    }
    final.push_back(temp);

    return final;
}