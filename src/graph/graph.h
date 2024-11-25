#pragma once

#include <vector>

#include "../module/module.h"

class AdjacencyListNode {
    public:
        AdjacencyListNode()
            : destinationCity(nullptr), routes(nullptr) {}

        // setters and getters
        City* getDestinationCity() const { return destinationCity; }
        void setDestinationCity(City* destinationCity) { this->destinationCity = destinationCity; }

        std::vector<Route*>* getRoutes() const { return routes; }
        void setRoutes(std::vector<Route*>* routes) { this->routes = routes; }

    private:
        City* destinationCity;
        std::vector<Route*>* routes;
};

class AdjacencyListPair {
    public:
        AdjacencyListPair()
            : theCity(nullptr), theNodes(nullptr) {}
        
        // setters and getters
        City* getCity() const { return theCity; }
        void setCity(City* theCity) { this->theCity = theCity; }

        std::vector<AdjacencyListNode>* getNodes() const { return theNodes; }
        void setNodes(std::vector<AdjacencyListNode>* theNodes) { this->theNodes = theNodes; }

    private:
        City* theCity;
        std::vector<AdjacencyListNode>* theNodes;
};

class AdjacencyList {
    public:
        AdjacencyList()
            : numberOfCities(0), numberOfRoutes(0), citiesList(nullptr), routesList(nullptr), adjacencyList(nullptr) {}

        // getters and setters
        int getNumberOfCities() const { return numberOfCities; }
        void setNumberOfCities(int numberOfCities) { this->numberOfCities = numberOfCities; }

        int getNumberOfRoutes() const { return numberOfRoutes; }
        void setNumberOfRoutes(int numberOfRoutes) { this->numberOfRoutes = numberOfRoutes; }

        std::vector<City*>* getCitiesList() const { return citiesList; }
        void setCitiesList(std::vector<City*>* citiesList) { this->citiesList = citiesList; }

        std::vector<Route*>* getRoutesList() const { return routesList; }
        void setRoutesList(std::vector<Route*>* routesList) { this->routesList = routesList; }

        std::vector<AdjacencyListPair>* getAdjacencyList() const { return adjacencyList; }
        void setAdjacencyList(std::vector<AdjacencyListPair>* adjacencyList) { this->adjacencyList = adjacencyList; }

        // methods
        bool isCityExists(City* city);
        bool isRouteExists(Route* route);
        void addCity(City* city);
        void addRoute(Route* route);

        void displayAdjacencyList();

    private:
        int numberOfCities;
        int numberOfRoutes;

        std::vector<City*>* citiesList; // list of cities
        std::vector<Route*>* routesList; // list of routes

        std::vector<AdjacencyListPair>* adjacencyList;
};


#include "graph.hpp"