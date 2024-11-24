#pragma once

#include "../module/module.h"
#include "../graph/graph.h"

class System {
    public:
        // constructors
        System() : graph(new AdjacencyList()) {}

        // getters and setters
        AdjacencyList* getGraph() const { return graph; }
        void setGraph(AdjacencyList* graph) { this->graph = graph; }

        // methods
        void launch();

        void addCity();

        void addRoute();

        void displaySystem();

    private:
        AdjacencyList* graph;
};

#include "system.hpp"