#include <vector>
#include <fstream>

#include "constants.h"
#include "Truck.h"
#include "utils.h"


/**
 * @brief represents a garage, storing trucks
 */
class Garage {

private:
    /**
     * @brief vector containing all of the trucks that have been loaded
     */
    std::vector<Truck> trucks;

public:
    /**
     * @brief creates a garage, populating the trucks vector
     */
    Garage();

    /**
     * @return reference to the trucks vector
     */
    std::vector<Truck>& get_trucks();

    /**
     * @param index index of the selected truck in the trucks vector
     * @return reference to the truck in the position index of the trucks vector
     */
    Truck& get_truck(int index);

    /**
     * @brief reads the file with information concerning the trucks, creating
     *        Truck objects and storing them in the trucks vector, with the
     *        corresponding information
     */
    void read_trucks();
};