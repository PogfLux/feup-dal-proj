cmake_minimum_required(VERSION 3.22)
project(DALProj)

set(CMAKE_CXX_STANDARD 20)

add_executable(DALProj main.cpp include/utils.h src/utils.cpp include/deliveries.h src/deliveries.cpp include/trucks.h src/trucks.cpp)
