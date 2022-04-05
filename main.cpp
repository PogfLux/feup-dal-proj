#include <iostream>
#include "include/Company.h"

int main() {

    /* for testing purposes */

    Company company;

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
