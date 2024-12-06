#pragma once

#include <iostream>
#include <memory>

#include "./main.h"

#include "../system/system.h"

void start() {
    std::cout << "Starting the server..." << std::endl;

    auto system = std::make_shared<System>();

    Server server(system);
    server.run();
    // server.test();

    std::cout << "Server started successfully" << std::endl;
}

