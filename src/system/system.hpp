#pragma once

#include <iostream>
#include <string>

#include "system.h"

#include "../module/module.h"
#include "../graph/graph.h"

// Launch the system
void System::launch() {
    std::cout << "System launched!" << std::endl;

    std::cout << "Generating graph..." << std::endl;
    graph = new Graph();
    if (graph != nullptr) {
        std::cout << "Graph generated!" << std::endl;
    } else {
        std::cout << "Failed to generate graph!" << std::endl;
    }
}

// Add a city to the system
void System::addCity() {
    
}

