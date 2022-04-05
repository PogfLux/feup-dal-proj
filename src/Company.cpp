#include "../include/Company.h"
#include "../include/constants.h"
#include "../include/utils.h"

Company::Company() {
    this->warehouse = Warehouse();
    this->garage = Garage();
}

Truck& Company::get_truck(int index) {
    return this->garage.get_trucks().at(index);
}

Delivery& Company::get_delivery(int index) {
    return this->warehouse.get_delivery(index);
}

int Company::get_garage_size() {
    return this->garage.get_trucks().size();
}

int Company::get_warehouse_size() {
    return this->warehouse.get_deliveries().size();
}

void Company::add_delivery(Delivery& delivery) {
    this->warehouse.get_deliveries().push_back(delivery);
}

void Company::add_truck(Truck& truck) {
    this->garage.get_trucks().push_back(truck);
}

void Company::read_deliveries() {
    std::ifstream f{DELIVERIES_PATH};
}
