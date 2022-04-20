#include "../include/Warehouse.h"

Warehouse::Warehouse() {
    read_deliveries(DEFAULT_DELIVERIES_PATH);
}

std::vector<Delivery>& Warehouse::get_deliveries() {
    return this->deliveries;
}

Delivery& Warehouse::get_delivery(int index) {
    return this->deliveries.at(index);
}

void Warehouse::read_deliveries(std::string path) {
    std::ifstream f{path};

    if (!deliveries.empty()) deliveries.clear();

    while (!f.eof()) {
        std::string line;
        std::vector<std::string> parsedLine;
        getline(f, line);

        if (line == "") break;

        parsedLine = split(line, ' ');

        Delivery delivery = Delivery(std::stoul(parsedLine.at(0)),
                                     std::stoul(parsedLine.at(1)),
                                     std::stoul(parsedLine.at(2)),
                                     std::stoul(parsedLine.at(3)));
        deliveries.push_back(delivery);

    }
}
