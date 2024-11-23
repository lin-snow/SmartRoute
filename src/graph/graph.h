#pragma once

#include <vector>
#include <unordered_map>

#include "../module/module.h"

class AdjacencyListNode {
    public:
        AdjacencyListNode()
            : destinationCity(nullptr), routes(nullptr) {}

        // getters and setters
        City* getDestinationCity() const { return destinationCity; }
        void setDestinationCity(City* destinationCity) { this->destinationCity = destinationCity; }

        std::vector<Route*>* getRoutes() { return routes; }
        void setRoutes(std::vector<Route*>* routes) { this->routes = routes; }

    private:
        City* destinationCity; // destination city
        std::vector<Route*>* routes; // routes
};

class AdjacencyList {
    public:
        AdjacencyList()
            : adjacencyList(nullptr) {}

        // getters and setters
        std::unordered_map<City*, std::vector<AdjacencyListNode>*>* getAdjacencyList() { return adjacencyList; }
        void setAdjacencyList(std::unordered_map<City*, std::vector<AdjacencyListNode>*>* adjacencyList) { this->adjacencyList = adjacencyList; }

    private:
        std::unordered_map<City*, std::vector<AdjacencyListNode>*>* adjacencyList;
};

class Graph {
    public:
        Graph()
            : citiesList(nullptr), routesList(nullptr), adjacencyList(nullptr) {}

        // setters and getters
        std::vector<City*>* getCitiesList() { return citiesList; }
        void setCitiesList(std::vector<City*>* citiesList) { this->citiesList = citiesList; }

        std::vector<Route*>* getRoutesList() { return routesList; }
        void setRoutesList(std::vector<Route*>* routesList) { this->routesList = routesList; }

        AdjacencyList* getAdjacencyList() { return adjacencyList; }
        void setAdjacencyList(AdjacencyList* adjacencyList) { this->adjacencyList = adjacencyList; }

        // methods
        void addCity(City* city);

    private:
        std::vector<City*>* citiesList;
        std::vector<Route*>* routesList;

        AdjacencyList* adjacencyList;
};

#include "graph.hpp"
