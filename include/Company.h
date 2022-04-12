#include "Warehouse.h"
#include "Garage.h"

#include <queue>
#include <memory>

class Company {

private:
    Warehouse warehouse;
    Garage garage;

public:
    Company();

	std::vector<Truck>* get_trucks();
	std::vector<Delivery>* get_deliveries();
    Truck& get_truck(int index);
    Delivery& get_delivery(int index);
    int get_warehouse_size();
    int get_garage_size();
    void add_truck(Truck& truck);
    void add_delivery(Delivery& delivery);

    void read_trucks();
    void read_deliveries();
};