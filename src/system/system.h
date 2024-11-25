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
        void addCity(City* theCity);
        bool isRouteValid(Route* route);
        void addRoute(Route* theRoute);
        void displaySystem();
        City* inputCity();
        Route* inputRoute();

        void loadData(); // load data from json file
        void saveData(); // save data to json file

    private:
        AdjacencyList* graph;
};

#include "system.hpp"
#include "../utils/jsonTool.hpp"