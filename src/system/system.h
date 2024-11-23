#pragma once

#include "../graph/graph.h"

class System
{
    public:
        // getters and setters
        Graph* getGraph() { return graph; }
        void setGraph(Graph* graph) { this->graph = graph; }

        // methods
        void launch();

        void addCity();

    private:
        Graph* graph;
};

#include "system.hpp"