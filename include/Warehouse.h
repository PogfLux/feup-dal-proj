#include <vector>
#include <fstream>

#include "constants.h"
#include "Delivery.h"
#include "utils.h"

/**
 * @brief represents a warehouse, storing deliveries
 */
class Warehouse {

private:
    /**
     * @brief vector containing all of the deliveries that have been loaded
     */
    std::vector<Delivery> deliveries;

public:
    /**
     * @brief creates a warehouse, populating the deliveries vector
     */
    Warehouse();

    /**
     * @return reference to the deliveries vector
     */
    std::vector<Delivery>& get_deliveries();

    /**
     * @param index index of the selected delivery in the deliveries vector
     * @return reference to the delivery in the position index of the deliveries vector
     */
    Delivery& get_delivery(int index);

    /**
     * @brief reads the file with information concerning the deliveries, creating
     *        Delivery objects and storing them in the deliveries vector, with the
     *        corresponding information
     *
     * @param path path to the file with the deliveries dataset to be loaded
     */
    void read_deliveries(std::string path);
};