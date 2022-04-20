#include <iostream>

/**
 * @brief represents a delivery
 */
class Delivery {
private:
    /**
     * @brief volume of the delivery
     */
    unsigned int volume;

    /**
     * @brief weight of the delivery
     */
    unsigned int weight;

    /**
     * @brief reward of the delivery
     */
    unsigned int reward;

    /**
     * @brief expected duration of the delivery
     */
    unsigned int expected_duration;

public:
    /**
     * @brief creates a new delivery
     *
     * @note will initialize all private variables at 0
     */
    Delivery();

    /**
     * @brief creates a new delivery
     *
     * @param volume volume of the delivery
     * @param weight weight of the delivery
     * @param reward reward of the delivery
     * @param expected_duration expected duration of the delivery
     */
    Delivery(unsigned volume, unsigned weight, unsigned reward, unsigned expected_duration);

    /**
     * @return the volume of the delivery
     */
    unsigned int get_volume() const;

    /**
     * @return the weight of the delivery
     */
    unsigned int get_weight() const;

    /**
     * @return the reward of the delivery
     */
    unsigned int get_reward() const;

    /**
     * @return the expected duration of the delivery
     */
    unsigned int get_duration() const;

    /**
     * @brief overloads the << operator, presenting the information of a delivery in a more human
     *        friendly fashion
     */
    friend std::ostream& operator << (std::ostream& out, const Delivery& delivery) {

        out << delivery.volume << ' ' << delivery.weight << ' ' << delivery.reward << ' ' << delivery.expected_duration;

        return out;
    }
};