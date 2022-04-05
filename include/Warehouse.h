#include <vector>
#include <fstream>

#include "constants.h"
#include "Delivery.h"
#include "utils.h"

class Warehouse {

private:
    std::vector<Delivery> deliveries;

public:
    Warehouse();
    std::vector<Delivery>& get_deliveries();
    Delivery& get_delivery(int index);
    void read_deliveries();
};