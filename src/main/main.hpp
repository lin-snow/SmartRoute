#pragma once

#include <iostream>

#include "./main.h"

#include "../system/system.h"

void start() {
    std::cout << "Starting the system..." << std::endl;

    System system;
    system.launch();

    // addCity();
    system.addCity();

    // addRoute();
    system.addRoute();

    // displaySystem();
    system.displaySystem();
}

