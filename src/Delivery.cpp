#include "../include/Delivery.h"

Delivery::Delivery() {
    this->volume = 0;
    this->weight = 0;
    this->reward = 0;
    this->expected_duration = 0;
}

Delivery::Delivery(unsigned int volume, unsigned int weight, unsigned int reward, unsigned int expected_duration) {
    this->volume = volume;
    this->weight = weight;
    this->reward = reward;
    this->expected_duration = expected_duration;
}

unsigned int Delivery::get_volume() const {
    return this->volume;
}

unsigned int Delivery::get_weight() const {
    return this->weight;
}

unsigned int Delivery::get_reward() const {
    return this->reward;
}

unsigned int Delivery::get_duration() const {
    return this->expected_duration;
}

