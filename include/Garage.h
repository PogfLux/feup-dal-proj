#include <vector>
#include <fstream>

#include "constants.h"
#include "Truck.h"
#include "utils.h"

class Garage {

private:
    std::vector<Truck> trucks;

public:
    Garage();
    std::vector<Truck>& get_trucks();
    Truck& get_truck(int index);
    void read_trucks();
};