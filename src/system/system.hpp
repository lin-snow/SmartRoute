#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <future>

#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"

#include "system.h"
#include "../server/server.h"
#include "../module/module.h"
#include "../graph/graph.h"

// Launch the system
void System::launch() {
    std::cout << "System launched!" << std::endl;
}

// Check if city is valid
bool System::isCityValid(City* city) {
    if (city == nullptr) {
        std::cout << "City is null" << std::endl;
        return false;
    }

    if (city->getName().empty()) {
        std::cout << "City name is empty" << std::endl;
        return false;
    }

    if (graph->isCityExists(city)) {
        std::cout << "City " << city->getName() << " with code " << city->getCityCode() << " already exists" << std::endl;
        return false;
    }

    return true;
}

// Check if route is valid
bool System::isRouteValid(Route* route) {
    if (route == nullptr) {
        std::cout << "Route is null" << std::endl;
        return false;
    }

    if (route->getFrom() == route->getTo()) {
        std::cout << "Route from and to cities are the same" << std::endl;
        return false;
    }

    if (route->getDistance() <= 0) {
        std::cout << "Route distance is invalid" << std::endl;
        return false;
    }

    if (route->getDuration() <= 0) {
        std::cout << "Route duration is invalid" << std::endl;
        return false;
    }

    if (route->getCost() <= 0) {
        std::cout << "Route cost is invalid" << std::endl;
        return false;
    }

    if (route->getVehicle() == nullptr) {
        std::cout << "Route vehicle is null" << std::endl;
        return false;
    }

    if (graph->isRouteExists(route)) {
        std::cout << "Route already exists" << std::endl;
        return false;
    }

    return true;
}

// Add city to the system
int System::addCity(City* theCity) {
    if (isCityValid(theCity)) {
        return graph->addCity(theCity);
    }
    return ERROR;
}

int System::deleteCity(int cityCode) {
    return graph->deleteCity(cityCode);
}

// Add route to the system
int System::addRoute(Route* theRoute) {
    if (isRouteValid(theRoute)) {
        return graph->addRoute(theRoute);
    }
    return ERROR;
}

int System::deleteRoute(int routeId, int from, int to) {
    if (routeId <= 0) {
        std::cout << "Invalid route id" << std::endl;
        return ERROR;
    }

    return graph->deleteRoute(routeId, from, to);
}

void System::displaySystem() {
    graph->displayAdjacencyList();
}

City* System::inputCity() {
    std::string name;
    int cityCode;

    std::cout << "Enter city name: ";
    std::cin >> name;

    std::cout << "Enter city code: ";
    std::cin >> cityCode;

    return new City(name, cityCode);
}

Route* System::inputRoute() {
    int from, to;
    long distance, duration, cost;
    int vehicleType;
    std::string vehicleCode;
    Time departureTime, arrivalTime;

    std::cout << "Enter from city code: ";
    std::cin >> from;

    std::cout << "Enter to city code: ";
    std::cin >> to;

    std::cout << "Enter distance: ";
    std::cin >> distance;

    std::cout << "Enter cost: ";
    std::cin >> cost;

    std::cout << "Enter vehicle type (0 for BUS, 1 for TRAIN): ";
    std::cin >> vehicleType;

    std::cout << "Enter vehicle code: ";
    std::cin >> vehicleCode;



    std::cout << "Enter departure time: " << std::endl;
    std::cout << "HH: "; int hour; std::cin >> hour;
    std::cout << "MM: "; int minute; std::cin >> minute;
    departureTime.setHour(hour);
    departureTime.setMinute(minute);

    std::cout << "Enter arrival time: " << std::endl;
    std::cout << "HH: "; std::cin >> hour;
    std::cout << "MM: "; std::cin >> minute;
    arrivalTime.setHour(hour);
    arrivalTime.setMinute(minute);

    duration = departureTime.diffInMinutes(arrivalTime);

    return new Route(from, to, distance, duration, new Vehicle((VehicleType)vehicleType, vehicleCode), departureTime, arrivalTime, cost);
}

int System::findAllRoutes(int from, int to, int vehicleType, std::vector<std::vector<Route*>>& result) {
    return graph->findAllRoutes(from, to, vehicleType, result);
}

int System::mostFastestWay(int from, int to, int vehicleType, std::vector<Route*>& result) {
    return graph->mostFastestWay(from, to, vehicleType, result);
}

int System::mostEconomicWay(int from, int to, int vehicleType, std::vector<Route*>& result) {
    return graph->mostEconomicWay(from, to, vehicleType, result);
}

// load data from json file
void System::loadData() {
    std::cout << "Loading data..." << std::endl;

    // file path
    std::string citiesPath = "data/cities.json";
    std::string routesPath = "data/routes.json";

    // using nlohmann json
    nlohmann::json citiesJson;
    std::ifstream citiesFile(citiesPath);
    if (citiesFile.is_open()) {
        citiesFile >> citiesJson;
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    // load cities
    for (nlohmann::json cityJson : citiesJson) {
        addCity(json2city(cityJson));
    }

    // load routes
    // using nlohmann json
    nlohmann::json routesJson;
    std::ifstream routesFile(routesPath);
    if (routesFile.is_open()) {
        routesFile >> routesJson;
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    // load routes
    for (nlohmann::json routeJson : routesJson) {
        addRoute(json2route(routeJson));
    }

    citiesFile.close();
}

// save data to json file
void System::saveData() {
    std::cout << "Saving data..." << std::endl;

    // file path
    std::string citiesPath = "data/cities.json";
    std::string routesPath = "data/routes.json";   

    // using nlohmann json
    nlohmann::json citiesJson;
    for (City* city : *graph->getCitiesList()) {
        citiesJson.push_back(city2json(city));
    }

    // std::cout << citiesJson.dump() << std::endl;
    std::string serialisedCitiesData = citiesJson.dump(4);

    // write to file
    std::ofstream citiesFile(citiesPath);

    if (citiesFile.is_open()) {
        citiesFile << serialisedCitiesData;
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    citiesFile.close();

    // save routes
    // using nlohmann json
    nlohmann::json routesJson;
    for (Route* route : *graph->getRoutesList()) {
        routesJson.push_back(route2json(route));
    }

    // std::cout << routesJson.dump() << std::endl;
    std::string serialisedRoutesData = routesJson.dump(4);

    // write to file
    std::ofstream routesFile(routesPath);

    if (routesFile.is_open()) {
        routesFile << serialisedRoutesData;
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    system("pause");
}

