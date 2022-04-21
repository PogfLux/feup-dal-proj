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

std::vector<Truck> *Company::get_trucks() {
	return &garage.get_trucks();
}

std::vector<Delivery> *Company::get_deliveries() {
	return &warehouse.get_deliveries();
}

std::tuple<int, int, double> Company::bin_packing(OPTIMIZATION opt) {
    std::vector<Delivery> deliveries = *get_deliveries();
    std::vector<Truck> trucks = *get_trucks();

    auto start = std::chrono::system_clock::now();
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
    }

    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    for (auto truck: remaining) {
        if (truck.first != 0 && truck.second != 0) {
            num_trucks++;
        }
    }

    return {num_trucks, delivered, time.count()};
}

std::tuple<int, int, double> Company::bin_packing_profit() {

    auto start = std::chrono::system_clock::now();

    std::vector<Truck> trucks = *this->get_trucks();
    std::sort(trucks.begin(), trucks.end(), [] (const Truck& a, const Truck& b) {
        return a.get_cost() < b.get_cost();
    });

    std::vector<Delivery> deliveries = *this->get_deliveries();
    std::sort(deliveries.begin(), deliveries.end(), [] (const Delivery& a, const Delivery& b) {
        return a.get_reward() > b.get_reward();
    });

    unsigned int num_trucks = 0, delivered = 0;
    int profit = 0;

    std::vector<std::pair<int, int>> remaining;

    for (int i = 0; i < this->get_garage_size(); i++) {
        remaining.push_back(std::make_pair(0, 0));
    }

    for (int i = 0; i < this->get_warehouse_size(); i++) {
        bool found = false;

        for (int j = 0; j < this->get_garage_size(); j++) {
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

    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    for (auto truck: remaining) {
        if (truck.first != 0 && truck.second != 0) {
            num_trucks++;
        }
    }

    if (delivered != this->get_warehouse_size()) {
        std::cout << "Not all deliveries will be done today! (" << delivered << '/' << this->get_warehouse_size() << ")\n";
    } else {
        std::cout << "All deliveries will be done today!\n";
    }

    return {num_trucks, profit, time.count()};
}

std::pair<int, double> Company::bin_packing_express() {

    auto start = std::chrono::system_clock::now();

    std::vector<Delivery> deliveries = *this->get_deliveries();
    std::sort(deliveries.begin(), deliveries.end(), [](const Delivery& a, const Delivery& b) {
        return a.get_duration() < b.get_duration();
    });


    unsigned int delivered = 0;
    int time_limit = 8*60*60; // 8 hours between 9AM and 5PM (in seconds)

    int i = 0;
    while (time_limit > 0 && i < this->get_warehouse_size()) {
            auto duration = deliveries.at(i).get_duration();
            time_limit -= duration;
            delivered++;
            i++;
    }

    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    return std::make_pair(delivered, time.count());
}


void Company::reload(CompanyTypes type) {
    switch (type) {
        case DEFAULT:
            warehouse.read_deliveries(DEFAULT_DELIVERIES_PATH);
            break;
        case DELIVERIES:
            warehouse.read_deliveries(DELIVERIES_DELIVERIES_PATH);
            break;
        case TRUCKS:
            warehouse.read_deliveries(TRUCKS_DELIVERIES_PATH);
            break;
    }
}
