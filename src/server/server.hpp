#pragma once

#include <iostream>
#include <string>
#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"

#include "../system/system.h"
#include "../utils/yamlTool.hpp"
#include "crow/middlewares/cors.h"

#include "server.h"

#include "../module/module.h"
#include "../graph/graph.h"
#include "../utils/jsonTool.hpp"


void Server::run() {
    // start server
    crow::App<crow::CORSHandler> app;

    // load data
    theSystem->loadData();
    theSystem->displaySystem();

    std::shared_ptr<System> serverSys = this->theSystem;

    // 获取 CORSHandler 中间件
    auto& cors = app.get_middleware<crow::CORSHandler>();

    // 全局 CORS 规则
    cors.global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests") // 自定义响应头
        .methods("GET"_method, "POST"_method, "OPTIONS"_method) // 支持的方法
        .origin("*") // 允许所有来源（生产环境需限制具体来源）
        .max_age(3600); // 预检请求缓存时间（秒）

    CROW_ROUTE(app, "/")
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, SmartRoute!";
        res["code"] = 200;

        return res;
    });


    /* PUBLIC CONTROLLER */
    CROW_ROUTE(app, "/data/get")
    ([serverSys](){
        // return crow_json;

        nlohmann::json response;

        // 构建城市列表
        nlohmann::json cities;
        for (City* city : *(serverSys->getGraph()->getCitiesList())) {
            cities.push_back(city2json(city));
        }
    
        // 包装成包含 "data" 和 "list" 的结构
        response["data"] = {
            {"list", cities}
        };
    
        std::cout << response.dump() << std::endl;
    
        // 返回构建的 JSON 数据
        crow::json::wvalue res = crow::json::load(response.dump());
        return res;
    });

    /* USER CONTROLLER */
    CROW_ROUTE(app, "/user/query").methods("GET"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, User Query!";
        res["code"] = 200;

        return res;
    });

    /* ADMIN CONTROLLER */
    CROW_ROUTE(app, "/admin/login").methods("POST"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin Login!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/logout").methods("POST"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin Logout!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/city/add").methods("POST"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin City Add!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/city/delete").methods("POST"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin City Delete!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/city/update").methods("PUT"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin City Update!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/route/add").methods("POST"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin Route Add!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/route/delete").methods("POST"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin Route Delete!";
        res["code"] = 200;

        return res;
    });

    CROW_ROUTE(app, "/admin/route/update").methods("PUT"_method)
    ([](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin Route Update!";
        res["code"] = 200;

        return res;
    });

    
    app.port(getPort()).multithreaded().run();
    
    return;
};


