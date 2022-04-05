cmake_minimum_required(VERSION 3.22)
project(DALProj)

set(CMAKE_CXX_STANDARD 20)

add_executable(DALProj main.cpp include/utils.h src/utils.cpp include/Delivery.h src/Delivery.cpp include/Truck.h src/Truck.cpp include/Warehouse.h src/Warehouse.cpp include/Company.h include/Garage.h src/Garage.cpp src/Company.cpp include/constants.h)
