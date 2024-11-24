#pragma once

#include <iostream>

#include "./main.h"

#include "../system/system.h"

void start() {
    std::cout << "Starting the system..." << std::endl;

    System system;
    system.launch();

    system.loadData();

    // addCity();
    // system.addCity(system.inputCity());
    // system.addCity(system.inputCity());

    // // displaySystem();
    // system.displaySystem();

    // // addRoute();
    // system.addRoute(system.inputRoute());

    // displaySystem();
    system.displaySystem();

    system.saveData();
}

