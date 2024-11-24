#pragma once

#include <iostream>
#include <vector>

#include "graph.h"

bool AdjacencyList::isCityExists(City* city) {
    if (city == nullptr) {
        std::cout << "City is null" << std::endl;
        return false;
    }

    if (citiesList == nullptr) {
        return false;
    }

    for (City* c : *citiesList) {
        if (c->getCityCode() == city->getCityCode() || c->getName() == city->getName()) {
            return true;
        }
    }

    return false;
}

bool AdjacencyList::isRouteExists(Route* route) {
    if (route == nullptr) {
        std::cout << "Route is null" << std::endl;
        return false;
    }

    if (routesList == nullptr) {
        return false;
    }

    // 遍历邻接表
    for (AdjacencyListPair adjacencyListPair : *adjacencyList) {
        // 查找起点城市
        if (adjacencyListPair.getCity()->getCityCode() == route->getFrom()) {
            // 找到起点城市  
            // 查找终点城市
            for (AdjacencyListNode adjacencyListNode : *adjacencyListPair.getNodes()) {
                if (adjacencyListNode.getDestinationCity()->getCityCode() == route->getTo()) {
                    // 找到终点城市
                    // 遍历路线
                    for (Route* r : *adjacencyListNode.getRoutes()) {
                        // 检查路线是否存在
                        // 检查是否使用相同的交通工具
                        if (r->getVehicle()->getVehicleType() == route->getVehicle()->getVehicleType()) {
                            // 检查是否使用相同的交通工具型号
                            if (r->getVehicle()->getVehicleCode() == route->getVehicle()->getVehicleCode()) {
                                // 检查时间是否冲突
                                if (route->getDepartureTime().diffInMinutes(r->getDepartureTime()) >= 0) {
                                    if (route->getArrivalTime().diffInMinutes(r->getDepartureTime()) <= 0 ) {
                                        return true;
                                    }
                                } else {
                                    if (route->getDepartureTime().diffInMinutes(r->getArrivalTime()) >= 0) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

void AdjacencyList::addCity(City* city) {
    if (city == nullptr) {
        std::cout << "City is null" << std::endl;
        return;
    }

    // check if city already exists
    if (isCityExists(city)) {
        std::cout << "City " << city->getName() << "with code " << city->getCityCode() << " already exists" << std::endl;
        return;
    }

    if (citiesList == nullptr) {
        citiesList = new std::vector<City*>();
    }

    citiesList->push_back(city);

    // add city to adjacency list
    if (adjacencyList == nullptr) {
        adjacencyList = new std::vector<AdjacencyListPair>();
    }

    AdjacencyListPair* adjacencyListPair = new AdjacencyListPair();
    adjacencyListPair->setCity(city);
    adjacencyListPair->setNodes(new std::vector<AdjacencyListNode>());

    adjacencyList->push_back(*adjacencyListPair);

    numberOfCities++;
};

void AdjacencyList::addRoute(Route* route) {
    if (route == nullptr) {
        std::cout << "Route is null" << std::endl;
    }

    if (routesList == nullptr) {
        routesList = new std::vector<Route*>();
    }

    // check if route already exists
    if (isRouteExists(route)) {
        std::cout << "Route " << route->getFrom() << " -> " << route->getTo() << " already exists" << std::endl;
        return;
    }

    routesList->push_back(route);

    // add route to adjacency list
    // 查找起点城市
    for (AdjacencyListPair adjacencyListPair : *adjacencyList) {
        if (adjacencyListPair.getCity()->getCityCode() == route->getFrom()) { // 找到起点城市
            // 查找终点城市
            for (AdjacencyListNode adjacencyListNode : *adjacencyListPair.getNodes()) {
                if (adjacencyListNode.getDestinationCity()->getCityCode() == route->getTo()) { // 找到终点城市
                    // 添加路线
                    adjacencyListNode.getRoutes()->push_back(route);

                    std::cout << "Route added successfully" << std::endl;

                    numberOfRoutes++;

                    return;
                }
            }

            // 如果终点城市不存在, 则添加终点城市
            AdjacencyListNode* adjacencyListNode = new AdjacencyListNode();
            for (City* city : *citiesList) {
                if (city->getCityCode() == route->getTo()) {
                    adjacencyListNode->setDestinationCity(city);
                    break;
                }
            }

            adjacencyListNode->setRoutes(new std::vector<Route*>());
            adjacencyListNode->getRoutes()->push_back(route);

            adjacencyListPair.getNodes()->push_back(*adjacencyListNode);
            break;
        }
    }

    std::cout << "Route added successfully" << std::endl;

    numberOfRoutes++;
}

void AdjacencyList::displayAdjacencyList() {
    if (adjacencyList == nullptr) {
        printf("Adjacency list is empty\n");
        return;
    }

    // display info
    std::cout << "-------------------------------------------------------------------- " << std::endl;
    std::cout << "Number of cities: " << numberOfCities << std::endl;
    std::cout << "Number of routes: " << numberOfRoutes << std::endl;

    for (City* city : *citiesList) {
        std::cout << "City: " << city->getName() << " (" << city->getCityCode() << ")" << std::endl;
    }

    if (routesList == nullptr) {
        std::cout << "No routes found" << std::endl;
    } else {
        for (Route* route : *routesList) {
            std::cout << "Route: " << route->getFrom() << " -> " << route->getTo() << " (" << route->getDistance() << " km, " << route->getDuration() << " minutes, " << route->getCost() << " yuan " << route->getVehicle()->getVehicleCode() << ")" << std::endl;
        }
    } 

    std::cout << "--------------------------------" << std::endl;

    // display adjacency list
    for (AdjacencyListPair adjacencyListPair : *adjacencyList) {
        std::cout << "City: " << adjacencyListPair.getCity()->getName() << " (" << adjacencyListPair.getCity()->getCityCode() << ")" << std::endl;

        std::cout << "********************************" << std::endl;

        for (AdjacencyListNode adjacencyListNode : *adjacencyListPair.getNodes()) {
            std::cout << "Destination city: " << adjacencyListNode.getDestinationCity()->getName() << " (" << adjacencyListNode.getDestinationCity()->getCityCode() << ")" << std::endl;

            std::cout << "Routes:" << std::endl;

            for (Route* route : *adjacencyListNode.getRoutes()) {
                std::cout << "Route: " << route->getFrom() << " -> " << route->getTo() << " (" << route->getDistance() << " km, " << route->getDuration() << " minutes, " << route->getCost() << " yuan " << 
                "vehicle: " << "[" << route->getVehicle()->getVehicleType() << "] " <<
                route->getVehicle()->getVehicleCode() << 
                "[" << route->getDepartureTime().getHour() << ":" << route->getDepartureTime().getMinute() << " -> " << route->getArrivalTime().getHour() << ":" << route->getArrivalTime().getMinute() << "]" <<
                ")" << std::endl;
            }

            std::cout << "********************************" << std::endl;
        }

        
        std::cout << "--------------------------------" << std::endl;
    }
}
