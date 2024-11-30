#pragma once


#include <iostream>
#include <string>
#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"
#include <thread>
#include <future>

#include "../system/system.h"
#include "../utils/yamlTool.hpp"
#include "../utils/webTool.hpp"
#include "crow/middlewares/cors.h"
#include "crow/multipart.h"

#include "server.h"

#include "../module/module.h"
#include "../graph/graph.h"
#include "../utils/jsonTool.hpp"

void Server::test() {
    std::cout << "Server test" << std::endl;

    theSystem->loadData();
    theSystem->displaySystem();

    // test the delete city function
    // theSystem->deleteCity(1);
    // theSystem->deleteCity(1);
    // // theSystem->deleteCity(1);
    // theSystem->deleteCity(2);

    // test the delete route function
    // theSystem->deleteRoute(16);

    // test the mostFastestWay function
    std::vector<std::vector<Route*>> result;
    theSystem->findAllRoutes(1, 3, 0, result);

    std::vector<Route*> fastestResult;

    theSystem->getGraph()->mostFastestWay(1, 3, 0, fastestResult);

    fastestResult.clear();

    theSystem->getGraph()->mostFastestWay(1, 3, 1, fastestResult);

    std::vector<Route*> economicResult;

    theSystem->getGraph()->mostEconomicWay(1, 3, 0, economicResult);

    economicResult.clear();

    theSystem->getGraph()->mostEconomicWay(1, 3, 1, economicResult);

    // theSystem->displaySystem();
}


void Server::run() {
    // start server
    crow::App<crow::CORSHandler> app;

    // load data
    theSystem->loadData();
    theSystem->displaySystem();

    // 启动服务器
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "请使用浏览器访问： http://" << getHost() << ":" << getPort() << " 进行使用 :) 关闭可在控制台按Ctrl + C!" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    std::shared_ptr<System> serverSys = this->theSystem;

    // 配置静态文件路径
    const std::string staticPath = getWebPath();

    // 获取 CORSHandler 中间件
    auto& cors = app.get_middleware<crow::CORSHandler>();

    // 全局 CORS 规则
    cors.global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests", "Content-Type") // 自定义请求头
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method) // 支持的方法
        .origin("*") // 允许所有来源（生产环境需限制具体来源）
        .max_age(3600); // 预检请求缓存时间（秒）

    // 提供静态资源
    CROW_ROUTE(app, "/assets/<string>")
        ([staticPath](const std::string& filename) {
            std::string filepath = staticPath + "/assets/" + filename;
            if (!std::filesystem::exists(filepath)) {
                return crow::response(404, "File Not Found");
            }

            std::string mimeType = getMimeType(filepath); // 获取 MIME 类型
            crow::response res(readFile(filepath));
            res.add_header("Content-Type", mimeType); // 设置 MIME 类型
            return res;
        });

    // 提供 index.html
    CROW_ROUTE(app, "/")
        ([staticPath]() {
            std::string filepath = staticPath + "/index.html";
            if (!std::filesystem::exists(filepath)) {
                return crow::response(404, "Index Not Found");
            }

            crow::response res(readFile(filepath));
            res.add_header("Content-Type", "text/html"); // 设置 MIME 类型
            return res;
        });

    CROW_ROUTE(app, "/favicon.ico")
        ([staticPath]() {
            std::string filepath = staticPath + "/favicon.ico";
            if (!std::filesystem::exists(filepath)) {
                return crow::response(404, "Index Not Found");
            }

            std::string mimeType = getMimeType(filepath); // 获取 MIME 类型
            crow::response res(readFile(filepath));
            res.add_header("Content-Type", mimeType); // 设置 MIME 类型
            return res;
        });

    /* PUBLIC CONTROLLER */
    CROW_ROUTE(app, "/api/data/get")
    ([serverSys](){
        // return crow_json;
        try {
            nlohmann::json response;

            // 构建城市列表
            nlohmann::json cities;
            for (City* city : *(serverSys->getGraph()->getCitiesList())) {
                cities.push_back(city2json(city));
            }
        
            // 包装成包含 "data" 和 "list" 的结构
            response["data"] = {
                {"cities", cities}
            };
        
            // 构建路线列表
            nlohmann::json routes;
            for (AdjacencyListPair pair : *(serverSys->getGraph()->getAdjacencyList())) {
                for (AdjacencyListNode node : *(pair.getNodes())) {
                    for (Route* route : *(node.getRoutes())) {
                        routes.push_back(route2json(route));
                    }
                }
            }

            // 包装成包含 "data" 和 "list" 的结构
            response["data"]["routes"] = routes;

            // 判断是否有数据
            if (cities.size() == 0 && routes.size() == 0) {
                response["msg"] = "No Data Found!";
                response["code"] = 401;
            } else if (cities.size() > 0 && routes.size() > 0) {
                response["msg"] = "Data Get Success!";
                response["code"] = 200;
            } else if (cities.size() > 0 && routes.size() == 0) {
                response["msg"] = "Routes Not Found!";
                response["code"] = 402;
            } else {
                response["msg"] = "Error!";
                response["code"] = 400;
            }
        
            // 返回构建的 JSON 数据
            crow::json::wvalue res = crow::json::load(response.dump());

            return res;
        } catch(std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;

            Result result(400, "Data Get Failed!", {});
            crow::json::wvalue res = crow::json::load(result.error().dump());
            return res;
        }
    });

    /* USER CONTROLLER */
    CROW_ROUTE(app, "/api/user/query").methods("GET"_method)
    ([serverSys](const crow::request& req){
        auto query = req.url_params;
        int from = std::stoi(query.get("from"));
        int to = std::stoi(query.get("to"));
        int vehicleType = std::stoi(query.get("vehicleType"));

        try {
            // 返回所有路线
            std::vector<std::vector<Route*>> allRoutes;
            serverSys->findAllRoutes(from, to, vehicleType, allRoutes);

            // 返回最快路线
            std::vector<Route*> fastestRoute;
            serverSys->mostFastestWay(from, to, vehicleType, fastestRoute);

            // 返回最省钱路线
            std::vector<Route*> economicRoute;
            serverSys->mostEconomicWay(from, to, vehicleType, economicRoute);

            nlohmann::json response;
            nlohmann::json data;
            nlohmann::json allRoutesData;
            nlohmann::json fastestRouteData;
            nlohmann::json economicRouteData;

            for (std::vector<Route*> routes : allRoutes) {
                nlohmann::json oneAvailblePlan;
                for (Route* r : routes) {
                    oneAvailblePlan.push_back(route2json(r));
                }
                allRoutesData.push_back(oneAvailblePlan);
            }

            for (Route* r : fastestRoute) {
                fastestRouteData.push_back(route2json(r));
            }

            for (Route* r : economicRoute) {
                economicRouteData.push_back(route2json(r));
            }

            data["allRoutes"] = allRoutesData;
            data["fastestRoute"] = fastestRouteData;
            data["economicRoute"] = economicRouteData;


            if (allRoutes.size() == 0 && fastestRoute.size() == 0 && economicRoute.size() == 0) {
                response["msg"] = "No Data Found!";
                response["code"] = 401;
            } else if (allRoutes.size() > 0 || fastestRoute.size() > 0 || economicRoute.size() > 0) {
                response["msg"] = "Query Success!";
                response["code"] = 200;
            } else {
                response["msg"] = "Error!";
                response["code"] = 400;
            }

            response["data"] = data;

            crow::json::wvalue res = crow::json::load(response.dump());
            
            return res;
        } catch (std::exception& e) {
            Result result(400, "Query Failed!", {});
            crow::json::wvalue res = crow::json::load(result.success().dump());
            return res;
        }
    });

    /* ADMIN CONTROLLER */
    CROW_ROUTE(app, "/api/admin/login").methods("POST"_method)
    ([](const crow::request& req){
        // return json data
        crow::multipart::message x(req);
        std::string username = x.get_part_by_name("username").body;
        std::string password = x.get_part_by_name("password").body;
        std::cout << "Username: " << username << std::endl;
        std::cout << "Password: " << password << std::endl;

        std::cout << "Admin Username: " << getAdminUsername() << std::endl;
        std::cout << "Admin Password: " << getAdminPassword() << std::endl;

        if (username == getAdminUsername() && password == getAdminPassword()) {
            Result result(200, "Admin Login Success!", {});
            crow::json::wvalue res = crow::json::load(result.success().dump());
            return res;
        } else {
            Result result(400, "Admin Login Failed!", {});
            crow::json::wvalue res = crow::json::load(result.error().dump());
            return res;
        }
    });

    CROW_ROUTE(app, "/api/admin/city/add").methods("POST"_method)
    ([serverSys](const crow::request& req){
        // return json data
        crow::multipart::message x(req);
        std::string name = x.get_part_by_name("name").body;
        std::string cityCode = x.get_part_by_name("cityCode").body;
        std::cout << "City Name: " << name << std::endl;
        std::cout << "City Code: " << cityCode << std::endl;

        City* city = new City(name, std::stoi(cityCode));
        if (serverSys->addCity(city) == ERROR) {
            Result result(400, "City Add Failed!", {});
            crow::json::wvalue res = crow::json::load(result.error().dump());
            return res;
        }

        Result result(200, "City added successfully", city2json(city));
        crow::json::wvalue res = crow::json::load(result.success().dump());


        return res;
    });

    CROW_ROUTE(app, "/api/admin/city/delete").methods("GET"_method)
    ([serverSys](const crow::request& req){        
        // delete city
        try {
            auto query = req.url_params;
            int theCityCode = std::stoi(query.get("cityCode"));

            std::cout << "City Code: " << theCityCode << std::endl;

            crow::json::wvalue res;

            if (serverSys->deleteCity(theCityCode) == ERROR) {
                Result result(400, "City Delete Failed!", {});
                crow::json::wvalue res = crow::json::load(result.error().dump());
                return res;
            } else {
                Result result(200, "City deleted successfully", {});
                crow::json::wvalue res = crow::json::load(result.success().dump());
                return res;
            }



            return res;
        } catch(std::exception& e) {
            Result result(400, "City Delete Failed!", {});
            crow::json::wvalue res = crow::json::load(result.error().dump());
            return res;
        }
    });

    // CROW_ROUTE(app, "/admin/city/update").methods("PUT"_method)
    // ([](){
    //     // return json data
    //     crow::json::wvalue res;
    //     res["msg"] = "Hello, Admin City Update!";
    //     res["code"] = 200;

    //     return res;
    // });

    CROW_ROUTE(app, "/api/admin/route/add").methods("POST"_method, "OPTIONS"_method)
    ([serverSys](const crow::request& req){
    
        crow::multipart::message x(req);
        std::string from = x.get_part_by_name("from").body;
        std::string to = x.get_part_by_name("to").body;
        std::string distance = x.get_part_by_name("distance").body;
        // std::string duration = x.get_part_by_name("duration").body;
        std::string cost = x.get_part_by_name("cost").body;
        std::string vehicleType = x.get_part_by_name("vehicleType").body;
        std::string vehicleCode = x.get_part_by_name("vehicleCode").body;
        std::string departureTime = x.get_part_by_name("departureTime").body;
        std::string arrivalTime = x.get_part_by_name("arrivalTime").body;

        std::cout << "From: " << from << std::endl;
        std::cout << "To: " << to << std::endl;
        std::cout << "Distance: " << distance << std::endl;
        // std::cout << "Duration: " << duration << std::endl;
        std::cout << "Cost: " << cost << std::endl;
        std::cout << "Vehicle Type: " << vehicleType << std::endl;
        std::cout << "Vehicle Code: " << vehicleCode << std::endl;
        std::cout << "Departure Time: " << departureTime << std::endl;
        std::cout << "Arrival Time: " << arrivalTime << std::endl;

        Time departureTimeObj(departureTime);
        Time arrivalTimeObj(arrivalTime);
        long duration = departureTimeObj.diffInMinutes(arrivalTimeObj);


        try {
            Route* route = new Route(std::stoi(from), std::stoi(to), std::stol(distance), duration, new Vehicle((VehicleType)std::stoi(vehicleType), vehicleCode), Time(departureTime), Time(arrivalTime), std::stol(cost));
            if (serverSys->addRoute(route) == ERROR) {
                Result result(400, "Route Add Failed!", {});
                crow::json::wvalue res = crow::json::load(result.error().dump());
                return res;
            }

            Result result(200, "Route added successfully", route2json(route));
            crow::json::wvalue res = crow::json::load(result.success().dump());

            return res;
        } catch(std::exception& e) {
            Result result(400, "Route Add Failed!", {});
            crow::json::wvalue res = crow::json::load(result.error().dump());
            return res;
        }
    });

    CROW_ROUTE(app, "/api/admin/route/delete").methods("GET"_method)
    ([serverSys](const crow::request& req){
        auto query = req.url_params;
        int theRouteId = std::stoi(query.get("routeId"));
        int from = std::stoi(query.get("from"));
        int to = std::stoi(query.get("to"));

        try {
            nlohmann::json response;

            // delete route
            if (serverSys->deleteRoute(theRouteId, from, to) == ERROR) {
                Result result(400, "Route Delete Failed!", {});
                crow::json::wvalue res = crow::json::load(result.error().dump());
                return res;
            } else {
                Result result(200, "Route deleted successfully", {});
                crow::json::wvalue res = crow::json::load(result.success().dump());
                return res;
            }



            crow::json::wvalue res = crow::json::load(response.dump());
            return res;
        } catch(std::exception& e) {
            Result result(400, "Route Delete Failed!", {});
            crow::json::wvalue res = crow::json::load(result.error().dump());
            return res;
        }
    });

    CROW_ROUTE(app, "/api/admin/shutdown").methods("GET"_method)
    ([serverSys](){
        // return json data
        crow::json::wvalue res;
        res["msg"] = "Hello, Admin Shutdown!";
        res["code"] = 200;

        // save data
        serverSys->saveData();
        serverSys->displaySystem();

        // shutdown server
        std::cout << "Server Shutdown!" << std::endl;
        exit(0);

        return res;
    });


    // CROW_ROUTE(app, "/admin/route/update").methods("PUT"_method)
    // ([](){
    //     // return json data
    //     crow::json::wvalue res;
    //     res["msg"] = "Hello, Admin Route Update!";
    //     res["code"] = 200;

    //     return res;
    // });
    
    // 动态路由返回 index.html（支持前端 Vue Router 的路径）
    CROW_ROUTE(app, "/<path>")
        ([staticPath](const std::string& path) {
            std::string indexFile = staticPath + "/index.html";
            if (!std::filesystem::exists(indexFile)) {
                return crow::response(404, "Index Not Found");
            }

            crow::response res(readFile(indexFile));
            res.add_header("Content-Type", "text/html"); // 设置 MIME 类型
            return res;
        });

    
    
    app.bindaddr(getHost()).port(getPort()).multithreaded().run();
    
    return;
};


