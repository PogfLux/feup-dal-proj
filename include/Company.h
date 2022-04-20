#include "Warehouse.h"
#include "Garage.h"

#include <queue>
#include <memory>
#include <chrono>

class Company;

/**
 * @brief possible implementations to be considered in some algorithms
 */
enum OPTIMIZATION {
    /**
     * @brief optimizing by the weight variable
     */
    WEIGHT,

    /**
     * @brief optimizing by the volume variable
     */
    VOLUME,

    /**
     * @brief optimizing by both the weight and volume variables
     */
    BOTH
};

/**
 * @brief the transportation company
 */
class Company {
private:
    /**
     * @brief warehouse containing information about deliveries
     */
    Warehouse warehouse;

    /**
     * @brief garage containing information about trucks
     */
    Garage garage;

public:
    /**
     * @brief creates a new company, initializes the warehouse and garage variables
     */
    Company();

    /**
     * @return pointer to the vector with all the deliveries registered to the company
     */
	std::vector<Truck>* get_trucks();

    /**
     * @return pointer to the vector with all the trucks registered to the company
     */
    std::vector<Delivery>* get_deliveries();

    /**
     * @param index the index of the truck in the garage's vector
     *
     * @return reference to the truck in index
     */
    Truck& get_truck(int index);

    /**
     * @param index the index of the delivery in the warehouse's vector
     *
     * @return reference to the delivery in index
     */
    Delivery& get_delivery(int index);

    /**
     * @return total number of deliveries registered
     */
    int get_warehouse_size();

    /**
    * @return total number of trucks registered
    */
    int get_garage_size();

    /**
     * @param truck the truck to be added to the garage
     *
     * @brief adds a truck to the garage
     */
    void add_truck(Truck& truck);

    /**
     * @param delivery the delivery to be added to the warehouse
     *
     * @brief adds a delivery to the warehouse
     */
    void add_delivery(Delivery& delivery);

    /**
     * @param opt the optimization to be considered in the algorithm
     *
     * @brief implementation of a bin packing algorithm. It follows an off-line first fit implementation,
     *        meaning the first best fit found will be selected, and the information regarding the trucks (bins)
     *        and the deliveries (packaging) will be sorted preemptively. The sorting is done according to user input.
     *
     * @return std::tuple with the following information: number of trucks used, number of deliveries done,
     *         time taken to execute the algorithm
     */
    std::tuple<int, int, double> bin_packing(OPTIMIZATION opt);
};