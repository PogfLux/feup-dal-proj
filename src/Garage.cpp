#include "../include/Garage.h"

Garage::Garage() {
    read_trucks();
}

std::vector<Truck>& Garage::get_trucks() {
    return this->trucks;
}

Truck& Garage::get_truck(int index) {
    return this->trucks.at(index);
}

void Garage::read_trucks() {
    std::ifstream f{TRUCKS_PATH};

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);

        if (line == "") break;

        parsedLine = split(line, ' ');

        Truck truck = Truck(std::stoul(parsedLine.at(0)),
                            std::stoul(parsedLine.at(1)),
                            std::stoul(parsedLine.at(2)));
        trucks.push_back(truck);

    }
}
