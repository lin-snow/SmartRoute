#include <iostream>
#include <string>
#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"
#include "fkYAML/node.hpp"

#include "./function/main.h"

using json = nlohmann::json;

int main() {
    // 设置UTF-8编码
    system("chcp 65001");
    
    crow::SimpleApp app;

    

    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    // deserialize the loaded file contents.
    fkyaml::node root = fkyaml::node::deserialize(ifs);

    // print the deserialized YAML nodes by serializing them back.
    std::cout << root << std::endl;

    CROW_ROUTE(app, "/")([](){
        printHello();
        // 返回json数据
        std::string jsonPath = "data/data.json";
        std::ifstream jsonFile(jsonPath);

        std::string jsonData((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
        
        jsonFile.close();

        crow::json::wvalue x;
        x = crow::json::load(jsonData.c_str(), jsonData.size());

        crow::json::wvalue res;
        res["msg"] = "Hello, SmartRoute!";
        res["code"] = 200;
        res["data"] = crow::json::load(jsonData.c_str(), jsonData.size());

        return res;
    });

    app.port(18080).multithreaded().run();
}

// std::cout << "Checking the routes..sb." << std::endl;
                            // // for (Route* r : *node.getRoutes()) { // 遍历所有路线
                            // //     std::cout << "giaogiao!!!!" << std::endl;
                            // //     // 检查是否有相同的交通工具 VehicleType
                            // //     if (r->getVehicle()->getVehicleType() == route->getVehicle()->getVehicleType()) {

                                    
                            // //         // 检查是否有相同的交通工具编号 VehicleCode
                            // //         if (r->getVehicle()->getVehicleCode().compare(route->getVehicle()->getVehicleCode()) == 0) {
                            // //             // 检查出发时间是否合理（是否处于departureTime和arrivalTime之间）
                            // //             if ((route->getDepartureTime().diffInMinutes(r->getDepartureTime()) >= 0) && 
                            // //                 (route->getDepartureTime().diffInMinutes(r->getArrivalTime()) <= 0)) {
                            // //                 return true;
                            // //             }
                            // //             // 检查到达时间是否合理（是否处于departureTime和arrivalTime之间）
                            // //             if ((route->getArrivalTime().diffInMinutes(r->getDepartureTime()) >= 0) && 
                            // //                 (route->getArrivalTime().diffInMinutes(r->getArrivalTime()) <= 0)) {
                            // //                 return true;
                            // //             }
                            // //         }
                            // //     }
                            // // }
                            // // for (Route* r : *(node.getRoutes())) {
                            // //     std::cout << "giaogiao!!!!" << std::endl;
                            // //     return true;
                            // // }
                            // std::vector<Route*>* routes = node.getRoutes();
                            // if (routes != nullptr) {
                            //     for (Route* r : *routes) {
                            //         std::cout << "giaogiao!!!!" << std::endl;
                            //         return true;

                            //     }
                            // }








                            
// class AdjacencyListNode {
//     public:
//         AdjacencyListNode()
//             : destinationCity(nullptr), routes(nullptr) {}

//         // getters and setters
//         City* getDestinationCity() const { return destinationCity; }
//         void setDestinationCity(City* destinationCity) { this->destinationCity = destinationCity; }

//         std::vector<Route*>* getRoutes() { return routes; }
//         void setRoutes(std::vector<Route*>* routes) { this->routes = routes; }

//     private:
//         City* destinationCity; // destination city
//         std::vector<Route*>* routes; // routes
// };

// class AdjacencyList {
//     public:
//         AdjacencyList()
//             : adjacencyList(nullptr) {}

//         // getters and setters
//         std::unordered_map<City*, std::vector<AdjacencyListNode>*>* getAdjacencyList() { return adjacencyList; }
//         void setAdjacencyList(std::unordered_map<City*, std::vector<AdjacencyListNode>*>* adjacencyList) { this->adjacencyList = adjacencyList; }

//         // methods
//         bool isCityExists(City* city);
//         bool isRouteExists(Route* route);
//         void addCity(City* city);
//         void addRoute(Route* route);

//         void displayAdjacencyList();

//     private:
//         std::unordered_map<City*, std::vector<AdjacencyListNode>*>* adjacencyList;
// };

// class Graph {
//     public:
//         Graph()
//             : numOfCities(0), numOfRoutes(0), citiesList(nullptr), routesList(nullptr), theAL(nullptr) {}

//         // setters and getters
//         std::vector<City*>* getCitiesList() const { return citiesList; }
//         void setCitiesList(std::vector<City*>* citiesList) { this->citiesList = citiesList; }

//         std::vector<Route*>* getRoutesList() const { return routesList; }
//         void setRoutesList(std::vector<Route*>* routesList) { this->routesList = routesList;}

//         AdjacencyList* getAdjacencyList() const { return theAL; }
//         void setAdjacencyList(AdjacencyList* adjacencyList) { this->theAL = adjacencyList; }

//         // methods
//         void addCity(City* city);
//         void addRoute(Route* route);

//     private:
//         int numOfCities; // number of cities
//         int numOfRoutes; // number of routes

//         std::vector<City *>* citiesList; // list of cities
//         std::vector<Route *>* routesList; // list of routes

//         AdjacencyList *theAL; // adjacency list
// };




// bool AdjacencyList::isCityExists(City* city) {
//     if (adjacencyList == nullptr) 
//         return false;

//     for (auto const& [key, val] : *adjacencyList) {
//         if (key->getCityCode() == city->getCityCode() || key->getName() == city->getName()) {
//             return true;
//         }
//     }

//     return false;
// }

// bool AdjacencyList::isRouteExists(Route* route) {
//     if (adjacencyList == nullptr) 
//         return false;

//     // the source city
//     for (auto const& [key, val] : *adjacencyList) {
//         if (key->getCityCode() == route->getFrom()) { // 找到起始城市
//             std::cout << "Found the source city!" << std::endl;
//             if (val == nullptr) {
//                 std::cout << "damn!!!!!!!!!!!" << std::endl;
//                 return false; // 当前城市没有任何路线
//             } else {
//                 std:: cout << "Checking the destination city..." << std::endl;
//                 std::cout << "val size: " << val->size() << std::endl;
//                 for (AdjacencyListNode node : *val) {
//                     if (node.getDestinationCity()->getCityCode() == route->getTo()) {
//                         std::cout << "Found the destination city!" << std::endl;

//                         // 找到相同的目的城市后，检查是否有相同的路线
//                         if (node.getRoutes() == nullptr) {
//                             return false; // 当前城市到目的城市没有任何路线
//                         } else {
//                             if (node.getRoutes()->size() == 0) {
//                                 std::cout << "No routes found!" << std::endl;
//                                 return false; // 当前城市到目的城市没有任何路线
//                             }
//                             return true;
//                         }
//                     }
//                 }
//             } 
//         }
//     }

//     return false;
// }

// void AdjacencyList::addCity(City* city) {
//     if (adjacencyList == nullptr) {
//         adjacencyList = new std::unordered_map<City*, std::vector<AdjacencyListNode>*>();
//     }

//     if (adjacencyList == nullptr) {
//         printf("OOPS! Something went wrong... \n");
//         return;
//     }

//     // add city to the adjacency list
//     adjacencyList->insert({city, nullptr});
//     std::cout << "City " << city->getName() << " with code " << city->getCityCode() << " added successfully!" << std::endl;
// }

// void AdjacencyList::addRoute(Route* route) {
//     if (adjacencyList == nullptr) {
//         printf("OOPS! Something went wrong... \n");
//         return;
//     }

//     // add route to the adjacency list
//     for (auto const& [key, val] : * adjacencyList) {
//         // 找到起始城市
//         if (key->getCityCode() == route->getFrom()) {
//             // 如果当前城市没有任何路线
//             if (val == nullptr) {
//                 std::cout << "val is null" << std::endl;
//                 // 创建一个新的路线
//                 std::vector<AdjacencyListNode>* routes = new std::vector<AdjacencyListNode>();
//                 if (routes == nullptr) {
//                     printf("OOPS! Something went wrong... \n");
//                     return;
//                 }

//                 // 将创建完的路线添加到当前城市
//                 adjacencyList->at(key) = routes;

//                 // 创建一个新的节点
//                 AdjacencyListNode node;
//                 for (auto const& [k, v] : * adjacencyList) {
//                     if (k->getCityCode() == route->getTo()) {
//                         node.setDestinationCity(k);
//                         break;
//                     }
//                 }

//                 // 创建一个新的路线
//                 std::vector<Route*>* r = new std::vector<Route*>();
//                 if (r == nullptr) {
//                     printf("OOPS! Something went wrong... \n");
//                     return;
//                 }
//                 node.setRoutes(r);

//                 // 将新的节点添加到当前城市
//                 std::cout << "pushing back the route..." << std::endl;
//                 node.getRoutes()->push_back(route);

//                 break;
//             } else {
//                 // 如果当前城市有路线
//                 for (AdjacencyListNode& node: *val) {
//                     // 找到目的城市
//                     if (node.getDestinationCity()->getCityCode() == route->getTo()) {
//                         // 如果当前城市到目的城市没有任何路线
//                         if (node.getRoutes() == nullptr || node.getRoutes()->size() == 0) {
//                             // 创建一个新的路线
//                             std::vector<Route*>* r = new std::vector<Route*>();
//                             if (r == nullptr) {
//                                 printf("OOPS! Something went wrong... \n");
//                                 return;
//                             }
//                             node.setRoutes(r);

//                             // 将路线添加进去
//                             std::cout << "no routes found, pushing back the route..." << std::endl;
//                             node.getRoutes()->push_back(route);

//                             break;
//                         }

//                         // 将路线添加进去
//                         std::cout << "has routes found, pushing back the route..." << std::endl;
//                         node.getRoutes()->push_back(route);

//                         break;
//                     } else { // 找不到目的城市
//                         // 创建一个新的结点
//                         std::cout << "creating a new node..." << std::endl;
//                         AdjacencyListNode n;
//                         for (auto const& [k, v] : * adjacencyList) {
//                             if (k->getCityCode() == route->getTo()) {
//                                 n.setDestinationCity(k);
//                                 break;
//                             }
//                         }

//                         // 创建一个新的路线
//                         std::vector<Route*>* r = new std::vector<Route*>();
//                         if (r == nullptr) {
//                             printf("OOPS! Something went wrong... \n");
//                             return;
//                         }
//                         n.setRoutes(r);

//                         // 将新的节点添加到当前城市
//                         val->push_back(n);

//                         // 将路线添加进去
//                         n.getRoutes()->push_back(route);

//                         break;
//                     }
//                 }
//             }
//         }
//     }
// }

// void AdjacencyList::displayAdjacencyList() {
//     if (adjacencyList == nullptr) {
//         printf("OOPS! Something went wrong... \n");
//         return;
//     }

//     for (auto const& [key, val] : *adjacencyList) {
//         std::cout << "City " << key->getName() << " with code " << key->getCityCode() << std::endl;
//         if (val == nullptr) {
//             std::cout << "No routes found!" << std::endl;
//         } else {
//             for (AdjacencyListNode node : *val) {
//                 std::cout << "Destination city: " << node.getDestinationCity()->getName() << " with code " << node.getDestinationCity()->getCityCode() << std::endl;
//                 if (node.getRoutes() == nullptr) {
//                     std::cout << "No routes found!" << std::endl;
//                 } else {
//                     for (Route* route : *(node.getRoutes())) {
//                         std::cout << "Route: " << route->getFrom() << " -> " << route->getTo() << " (" << route->getDistance() << " km, " << route->getDuration() << " minutes, " << route->getCost() << " yuan " << route->getVehicle()->getVehicleCode() << ")" << std::endl;
//                     }
//                 }
//             }
//         }
//     }
// }

// void Graph::addCity(City* city) {
//     if (citiesList == nullptr && theAL == nullptr) {
//         citiesList = new std::vector<City*>();
//         theAL = new AdjacencyList();
//     }

//     if (citiesList == nullptr || theAL == nullptr) {
//         printf("OOPS! Something went wrong... \n");
//         return;
//     }

//     if (theAL->isCityExists(city)) {
//         printf("City %s with code %d already exists!\n", city->getName().c_str(), city->getCityCode());
//         return;
//     }

//     citiesList->push_back(city);

//     // add city to the adjacency list
//     theAL->addCity(city);

//     // update number of cities
//     numOfCities++;

//     printf("City %s with code %d added successfully!\n", city->getName().c_str(), city->getCityCode());
// }

// void Graph::addRoute(Route* route) {
//     if (routesList == nullptr) {
//         routesList = new std::vector<Route*>();
//     }

//     if (routesList == nullptr) {
//         printf("OOPS! Something went wrong... \n");
//         return;
//     }

//     if (theAL->isRouteExists(route)) {
//         printf("Route from city %d to city %d already exists!\n", route->getFrom(), route->getTo());
//         return;
//     }

//     routesList->push_back(route);
    
//     // add route to the adjacency list
//     theAL->addRoute(route);

//     // update number of routes
//     numOfRoutes++;

//     printf("Route from city %d to city %d added successfully!\n", route->getFrom(), route->getTo());
// }




// // 定义一个从记录从起点到每个城市的最短费用
    // std::unordered_map<int, long> recordTable; // 记录到达每个城市的最短费用
    // // 将每个值初始化为无穷大
    // for (City* city : *citiesList) {
    //     recordTable[city->getCityCode()] = std::numeric_limits<long>::max();
    // }   

    // // 起点费用为 0
    // recordTable[from] = 0;

    // // 定义一个优先队列 （定义为 <费用, 城市>）
    // std::priority_queue<std::pair<long, int>, std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> pq;
    // pq.push(std::make_pair(0, from));

    // // 定义一个记录路径的表 (key: cityCode, value: previous cityCode)
    // std::unordered_map<int, int> pathTable;

    // // 开始遍历
    // while (!pq.empty()) {
    //     // 取出队列中的第一个元素
    //     std::pair<long, int> top = pq.top();
    //     pq.pop();

    //     // 取出城市编号
    //     int cityCode = top.second;
    //     // 取出费用
    //     long cost = top.first;

    //     // 如果已经访问过该城市，则跳过
    //     if (recordTable[cityCode] < cost) { // 如果访问费用小于当前费用，则跳过
    //         continue;
    //     }

    //     // 遍历邻接表
    //     for (AdjacencyListPair pair : *adjacencyList) {
    //         if (pair.getCity()->getCityCode() == cityCode) { // 找到起点城市
    //             // 遍历该城市到其他城市的路线
    //             for (AdjacencyListNode node : *pair.getNodes()) {
    //                 // 遍历每一个邻接城市节点
    //                 for (Route* route : *node.getRoutes()) {
    //                     // 遍历每一条路线
    //                     // 判断是否是同一种交通工具
    //                     if (route->getVehicle()->getVehicleType() == vehicleType) {
    //                         // 判断是否是最短费用
    //                         if (cost + route->getCost() < recordTable[route->getTo()]) {
    //                             recordTable[route->getTo()] = cost + route->getCost();
    //                             pq.push(std::make_pair(cost + route->getCost(), route->getTo()));
    //                             pathTable[route->getTo()] = cityCode;
    //                             // 存储route
    //                             result.push_back(route);
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // // 判断是否可达
    // if (recordTable[to] == std::numeric_limits<long>::max()) {
    //     std::cout << "No way to reach" << std::endl;
    //     return ERROR;
    // }

    // // 回溯路径
    // std::vector<int> path;
    // int currentCity = to;
    // while (currentCity != from) {
    //     path.push_back(currentCity);
    //     currentCity = pathTable[currentCity];
    // }
    // path.push_back(from);

    // // 反转路径
    // std::reverse(path.begin(), path.end());

    // // 输出结果
    // std::cout << "From " << from << " to " << to << " by " << vehicleType << std::endl;

    // std::cout << "The most economic way is: " << std::endl;
    // std::cout << "Cost: " << recordTable[to] << " yuan" << std::endl;

    // // 输出路径
    // std::cout << "Path: ";
    // for (Route* route : result) {
    //     std::cout << route->getFrom() << " -> ";
    // }
    // std::cout << to << std::endl;