#include <iostream>

class Delivery {

private:
    unsigned int volume;
    unsigned int weight;
    unsigned int reward;
    unsigned int expected_duration;

public:
    Delivery();
    Delivery(unsigned volume, unsigned weight, unsigned reward, unsigned expected_duration);
    unsigned int get_volume() const;
    unsigned int get_weight() const;
    unsigned int get_reward() const;
    unsigned int get_duration() const;

    friend std::ostream& operator << (std::ostream& out, const Delivery& delivery) {

        out << delivery.volume << ' ' << delivery.weight << ' ' << delivery.reward << ' ' << delivery.expected_duration;

        return out;
    }

	bool operator <(const Delivery& d) const {
		return get_weight() > d.get_weight() || get_volume() > d.get_volume();
	}
};