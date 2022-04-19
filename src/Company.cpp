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

std::vector<Truck> *Company::get_trucks() {
	return &garage.get_trucks();
}

std::vector<Delivery> *Company::get_deliveries() {
	return &warehouse.get_deliveries();
}

std::pair<int, int> Company::bin_packing(OPTIMIZATION opt) {
    std::vector<Delivery> deliveries = *get_deliveries();
    std::vector<Truck> trucks = *get_trucks();
    switch (opt) {
        case WEIGHT:
            std::sort(deliveries.begin(), deliveries.end(), [](Delivery &a, Delivery &b){
                return a.get_weight() > b.get_weight();
            });
            std::sort(trucks.begin(), trucks.end(), [](Truck &a, Truck &b){
                return a.get_max_weight() > b.get_max_weight();
            });
            break;
        case VOLUME:
            std::sort(deliveries.begin(), deliveries.end(), [](Delivery &a, Delivery &b){
                return a.get_volume() > b.get_volume();
            });
            std::sort(trucks.begin(), trucks.end(), [](Truck &a, Truck &b){
                return a.get_max_volume() > b.get_max_volume();
            });
            break;
        case BOTH:
            std::sort(deliveries.begin(), deliveries.end(), [](Delivery &a, Delivery &b){
                return a.get_weight() + a.get_volume() > b.get_weight() + b.get_volume();
            });
            std::sort(trucks.begin(), trucks.end(), [](Truck &a, Truck &b){
                return a.get_max_weight() + a.get_max_volume() > b.get_max_weight() + b.get_max_volume();
            });
            break;
    }

    unsigned int num_trucks = 0, delivered = 0;
    std::vector<std::pair<int, int>> remaining; // weight, volume

    for (auto truck: trucks) {
        remaining.push_back(std::make_pair(0, 0));
    }


    for (int i{0}; i < get_warehouse_size(); i++) {
        bool found = false;

        for (int j{0}; j < get_garage_size(); j++) {
            int rem_truck_wei = (trucks.at(j).get_max_weight() + remaining.at(j).first) - deliveries.at(i).get_weight();
            int rem_truck_vol = (trucks.at(j).get_max_volume() + remaining.at(j).second) - deliveries.at(i).get_volume();
            if (rem_truck_wei >= 0 && rem_truck_vol >= 0) {
                remaining.at(j).first -= get_delivery(i).get_weight();
                remaining.at(j).second -= get_delivery(i).get_volume();

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

    return std::make_pair(num_trucks, delivered);
}
