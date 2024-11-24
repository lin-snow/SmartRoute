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

void System::addCity() {
    City* city1 = new City("A", 1);
    City* city2 = new City("B", 2);
    City* city3 = new City("C", 3);
    City* city4 = new City("B", 4);
    City* city5 = new City("C", 1);

    graph->addCity(city1);
    graph->addCity(city2);
    graph->addCity(city3);
    graph->addCity(city4);
    graph->addCity(city5);
}

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

    graph->addRoute(route1);
    graph->addRoute(route2);
    graph->addRoute(route3);
    graph->addRoute(route4);
    graph->addRoute(route5);
}

void System::displaySystem() {
    graph->displayAdjacencyList();
}

// void System::addRoute() {
//     graph->addRoute();
// }

// void System::displaySystem() {
//     graph->displayAdjacencyList();
// }

// // Add a city to the system
// void System::addCity() {
//     std::string cityName;
//     int cityCode;

//     // std::cout << "Enter the city name: ";
//     // std::cin >> cityName;

//     // std::cout << "Enter the city code: ";
//     // std::cin >> cityCode;

//     City* city1 = new City("A", 1);
//     City* city2 = new City("B", 2);
//     City* city3 = new City("C", 3);

//     graph->addCity(city1);
//     graph->addCity(city2);
//     graph->addCity(city3);

//     // if (city != nullptr) {
//     //     graph->addCity(city);
//     // } else {
//     //     std::cout << "Failed to add city!" << std::endl;
//     // }
// }

// // Add a route to the system
// void System::addRoute() {
//     int from, to;
//     long distance, duration, cost;
//     int vehicleType;
//     std::string vehicleCode;
//     int departureHour, departureMinute;
//     int arrivalHour, arrivalMinute;

//     // std::cout << "Enter the city code of the source city: ";
//     // std::cin >> from;

//     // std::cout << "Enter the city code of the destination city: ";
//     // std::cin >> to;

//     // std::cout << "Enter the distance: ";
//     // std::cin >> distance;

//     // std::cout << "Enter the duration: ";
//     // std::cin >> duration;

//     // std::cout << "Enter the cost: ";
//     // std::cin >> cost;

//     // std::cout << "Enter the vehicle type (0 for train, 1 for plane): ";
//     // std::cin >> vehicleType;

//     // std::cout << "Enter the vehicle code: ";
//     // std::cin >> vehicleCode;

//     // std::cout << "Enter the departure time (HH MM): ";
//     // std::cin >> departureHour >> departureMinute;

//     // std::cout << "Enter the arrival time (HH MM): ";
//     // std::cin >> arrivalHour >> arrivalMinute;

//     std::cout << "generating route..." << std::endl;
//     system("pause");

//     Vehicle* vehicle = new Vehicle(static_cast<VehicleType>(0), "G1234");
//     Time departureTime(8, 10);
//     Time arrivalTime(8, 30);
//     duration = departureTime.diffInMinutes(arrivalTime);

//     Route* route1 = new Route(1, 2, 1000, duration, vehicle, departureTime, arrivalTime, 100);
//     Route* route2 = new Route(2, 3, 2000, duration, vehicle, departureTime, arrivalTime, 200);
//     Route* route3 = new Route(1, 2, 1000, duration, vehicle, departureTime, arrivalTime, 300);

//     std::cout << "Route generated!" << std::endl;
//     std::cout << "Adding route to the graph..." << std::endl;
//     system("pause");

//     graph->addRoute(route1);
//     graph->addRoute(route3);
//     graph->addRoute(route2);


//     // if (route != nullptr) {
//     //     graph->addRoute(route);
//     // } else {
//     //     std::cout << "Failed to add route!" << std::endl;
//     // }
// }

// // Display the system
// void System::displaySystem() {
//     // Display the cities
//     std::cout << "Cities:" << std::endl;

//     if (graph->getCitiesList() != nullptr) {
//         for (City* city : *graph->getCitiesList()) {
//             std::cout << city->getName() << " (" << city->getCityCode() << ")" << std::endl;
//         }
//     } else {
//         std::cout << "No cities found!" << std::endl;
//     }

//     // Display the routes
//     std::cout << "Routes:" << std::endl;

//     // 遍历路线
//     if (graph->getRoutesList() != nullptr) {
//         for (Route* route : *graph->getRoutesList()) {
//             std::cout << "Route: " << route->getFrom() << " -> " << route->getTo() << " (" << route->getDistance() << " km, " << route->getDuration() << " minutes, " << route->getCost() << " yuan " << route->getVehicle()->getVehicleCode() << ")" << std::endl;
//         }
//     } else {
//         std::cout << "No routes found!" << std::endl;
//     }

//     // 遍历邻接表
//     graph->getAdjacencyList()->displayAdjacencyList();

//     system("pause");
// }

