#pragma once

#include <string>

#include "../module/module.h"
#include "../graph/graph.h"

#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"

class System {
    public:
        // constructors
        System() : graph(new AdjacencyList()) {}

        // getters and setters
        AdjacencyList* getGraph() const { return graph; }
        void setGraph(AdjacencyList* graph) { this->graph = graph; }

        // methods
        void launch();
        bool isCityValid(City* city);
        int addCity(City* theCity);
        int deleteCity(int cityCode);
        int updateCity(City* oldCity, City* newCity);
        bool isRouteValid(Route* route);
        int addRoute(Route* theRoute);
        int deleteRoute(int routeId,int from, int to);
        void displaySystem();
        City* inputCity();
        Route* inputRoute();

        int findAllRoutes(int from, int to, int vehicleType, std::vector<std::vector<Route*>>& result);
        int mostFastestWay(int from, int to, int vehicleType, std::vector<Route*>& result);
        int mostEconomicWay(int from, int to, int vehicleType, std::vector<Route*>& result);

        void loadData(); // load data from json file
        void saveData(); // save data to json file

    private:
        AdjacencyList* graph;
};

#include "system.hpp"
#include "../utils/jsonTool.hpp"