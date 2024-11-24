#pragma once

#include <iostream>
#include <string>

#include "system.h"

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
void System::addCity() {
    City* city1 = new City("A", 1);
    City* city2 = new City("B", 2);
    City* city3 = new City("C", 3);
    City* city4 = new City("B", 4);
    City* city5 = new City("C", 1);


    if (isCityValid(city1)) {
        graph->addCity(city1);
    }
    if (isCityValid(city2)) {
        graph->addCity(city2);
    }
    if (isCityValid(city3)) {
        graph->addCity(city3);
    }
    if (isCityValid(city4)) {
        graph->addCity(city4);
    }
    if (isCityValid(city5)) {
        graph->addCity(city5);
    }
}

// Add route to the system
void System::addRoute() {
    Vehicle* vehicle = new Vehicle(static_cast<VehicleType>(0), "G1234");
    Vehicle* vehicle2 = new Vehicle(static_cast<VehicleType>(1), "TA1234");
    Time departureTime(8, 10);
    Time departureTime2(8, 31);
    Time arrivalTime(8, 30);
    Time arrivalTime2(8, 40);
    long duration = departureTime.diffInMinutes(arrivalTime);
    long duration2 = departureTime2.diffInMinutes(arrivalTime2);

    Route* route1 = new Route(1, 2, 1000, duration, vehicle, departureTime, arrivalTime, 100);
    Route* route2 = new Route(2, 3, 2000, duration, vehicle, departureTime, arrivalTime, 200);
    Route* route3 = new Route(1, 3, 1000, duration, vehicle, departureTime, arrivalTime, 300);
    Route* route4 = new Route(1, 2, 1000, duration2, vehicle, departureTime2, arrivalTime2, 400);
    Route* route5 = new Route(1, 2, 1000, duration2, vehicle2, departureTime2, arrivalTime2, 500);

    if (isRouteValid(route1)) {
        graph->addRoute(route1);
    }
    if (isRouteValid(route2)) {
        graph->addRoute(route2);
    }
    if (isRouteValid(route3)) {
        graph->addRoute(route3);
    }
    if (isRouteValid(route4)) {
        graph->addRoute(route4);
    }
    if (isRouteValid(route5)) {
        graph->addRoute(route5);
    }
}

void System::displaySystem() {
    graph->displayAdjacencyList();
}
