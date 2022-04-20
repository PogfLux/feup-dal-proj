#ifndef DALPROJ_CONSTANTS_H
#define DALPROJ_CONSTANTS_H

#include <string>

/**
 * @brief path to the file with the trucks information (default dataset)
 */
const std::string DEFAULT_TRUCKS_PATH = "./resources/carrinhas_default.txt";

/**
 * @brief path to the file with the deliveries information (default dataset)
 */
const std::string DEFAULT_DELIVERIES_PATH = "./resources/encomendas_default.txt";

/**
 * @brief path to the file with the deliveries information (trucks skewed dataset)
 */
const std::string TRUCKS_DELIVERIES_PATH = "./resources/encomendas_trucks.txt";

/**
 * @brief path to the file with the deliveries information (deliveries skewed dataset)
 */
const std::string DELIVERIES_DELIVERIES_PATH = "./resources/encomendas_deliveries.txt";


#endif //DALPROJ_CONSTANTS_H
