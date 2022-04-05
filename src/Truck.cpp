#include "../include/Truck.h"

Truck::Truck() {
    this->max_volume = 0;
    this->max_weight = 0;
    this->transportation_cost = 0;
}

Truck::Truck(unsigned int max_volume, unsigned int max_weight, unsigned int transportation_cost) {
    this->max_volume = max_volume;
    this->max_weight = max_weight;
    this->transportation_cost = transportation_cost;
}

unsigned int Truck::get_max_volume() {
    return this->max_volume;
}

unsigned int Truck::get_max_weight() {
    return this->max_weight;
}

unsigned int Truck::get_cost() {
    return this->transportation_cost;
}