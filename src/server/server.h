#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "nlohmann/json.hpp"

#include "../system/system.h"

#include "../module/module.h"
#include "../graph/graph.h"

class Server {
    public:
        Server(std::shared_ptr<System> sys)
            : theSystem(sys) {}

        void run();
        void test();

    private:
        // crow::SimpleApp app;
        crow::App<crow::CORSHandler> app;
        std::shared_ptr<System> theSystem;
};

class Result {
    public:
        Result(int code, std::string msg, nlohmann::json data)
            : code(code), msg(msg), data(data) {}

        nlohmann::json success() {
            nlohmann::json response;
            response["code"] = code;
            response["msg"] = msg;
            response["data"] = data;

            return response;
        }

        nlohmann::json error() {
            nlohmann::json response;
            response["code"] = code;
            response["msg"] = msg;
            response["data"] = data;

            return response;
        }
        
    private:
        int code;
        std::string msg;
        nlohmann::json data;
};



#include "server.hpp"