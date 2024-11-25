#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"

#include "../system/system.h"

#include "../module/module.h"
#include "../graph/graph.h"

class Server {
    public:
        Server(std::shared_ptr<System> sys)
            : theSystem(sys) {}

        void run();

    private:
        crow::SimpleApp app;
        std::shared_ptr<System> theSystem;
};



#include "server.hpp"