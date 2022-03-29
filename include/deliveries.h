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

};