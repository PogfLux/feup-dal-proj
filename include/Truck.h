#include <iostream>

class Truck {

private:
    unsigned int max_volume;
    unsigned int max_weight;
    unsigned int transportation_cost;

public:
    Truck();
    Truck(unsigned max_volume, unsigned max_weight, unsigned transportation_cost);
    unsigned int get_max_volume();
    unsigned int get_max_weight();
    unsigned int get_cost();

    friend std::ostream& operator << (std::ostream& out, const Truck& truck) {
        out << truck.max_volume << ' ' << truck.max_weight << ' ' << truck.transportation_cost;
        return out;
    }
};