#pragma once

#include <vector>
#include <memory>
#include <unordered_set>

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
            : numberOfCities(0), numberOfRoutes(0), citiesList(nullptr), adjacencyList(nullptr) {}

        // getters and setters
        int getNumberOfCities() const { return numberOfCities; }
        void setNumberOfCities(int numberOfCities) { this->numberOfCities = numberOfCities; }

        int getNumberOfRoutes();
        void setNumberOfRoutes(int numberOfRoutes) { this->numberOfRoutes = numberOfRoutes; }

        std::vector<City*>* getCitiesList() const { return citiesList; }
        void setCitiesList(std::vector<City*>* citiesList) { this->citiesList = citiesList; }

        std::vector<AdjacencyListPair>* getAdjacencyList() const { return adjacencyList; }
        void setAdjacencyList(std::vector<AdjacencyListPair>* adjacencyList) { this->adjacencyList = adjacencyList; }

        // methods
        bool isCityExists(City* city);
        bool isRouteExists(Route* route);
        int addCity(City* city);
        int deleteCity(int cityCode);
        int updateCity(City* oldCity, City* newCity);
        int addRoute(Route* route);
        int deleteRoute(int routeId, int from, int to);
        int updateRoute(long routeId, Route* newRoute);

        void displayAdjacencyList();

        // algorithms
        void dfsFindRoutes(int from, int to, int vehicleType, std::vector<std::vector<Route*>>& result, 
                            std::vector<Route*> currentRoute, std::unordered_set<int> visited, 
                            std::vector<AdjacencyListPair>* adjacencyList, Time previousArrivalTime);
                            
        int findAllRoutes(int from, int to, int vehicleType, std::vector<std::vector<Route*>>& result);
        int mostFastestWay(int from, int to, int vehicleType, std::vector<Route*>& result);
        int mostEconomicWay(int from, int to, int vehicleType, std::vector<Route*>& result);
        int leastTransferWay(int from, int to, int vehicleType, std::vector<Route*>& result);

    private:
        int numberOfCities;
        int numberOfRoutes;

        std::vector<City*>* citiesList; // list of cities

        std::vector<AdjacencyListPair>* adjacencyList;
};


#include "graph.hpp"
