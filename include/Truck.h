#include <iostream>

/**
 * @brief represents a truck
 */
class Truck {
private:
    /**
     * @brief maximum volume the truck can carry
     */
    unsigned int max_volume;

    /**
     * @brief maximum weight the truck can carry
     */
    unsigned int max_weight;

    /**
     * @brief transportation cost associated with operating the truck
     */
    unsigned int transportation_cost;

public:
    /**
     * @brief creates a new trucl
     *
     * @note will initialize all private variables at 0
     */
    Truck();

    /**
     * @brief creates a new delivery
     *
     * @param max_volume maximum volume of the truck
     * @param max_weight maximum weight of the truck
     * @param transportation_cost transportation cost of operating the truck
     */
    Truck(unsigned max_volume, unsigned max_weight, unsigned transportation_cost);

    /**
     * @return the maximum volume the truck can carry
     */
    unsigned int get_max_volume() const;

    /**
     * @return the maximum weight the truck can carry
     */
    unsigned int get_max_weight() const;

    /**
     * @return the transportation cost of operating the truck
    */
    unsigned int get_cost() const;

    /**
     * @brief overloads the << operator, presenting the information of a truck in a more human
     *        friendly fashion
     */
    friend std::ostream& operator << (std::ostream& out, const Truck& truck) {
        out << truck.max_volume << ' ' << truck.max_weight << ' ' << truck.transportation_cost;
        return out;
    }
};