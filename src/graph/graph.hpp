#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>


#include "graph.h"

bool AdjacencyList::isCityExists(City* city) {
    if (city == nullptr) {
        std::cout << "City is null" << std::endl;
        return false;
    }

    if (citiesList == nullptr) {
        return false;
    }

    for (City* c : *citiesList) {
        if (c->getCityCode() == city->getCityCode() || c->getName() == city->getName()) {
            return true;
        }
    }

    return false;
}

bool AdjacencyList::isRouteExists(Route* route) {
    if (route == nullptr) {
        std::cout << "Route is null" << std::endl;
        return false;
    }

    if (routesList == nullptr) {
        return false;
    }

    // 遍历邻接表
    for (AdjacencyListPair adjacencyListPair : *adjacencyList) {
        // 查找起点城市
        if (adjacencyListPair.getCity()->getCityCode() == route->getFrom()) {
            // 找到起点城市  
            // 查找终点城市
            for (AdjacencyListNode adjacencyListNode : *adjacencyListPair.getNodes()) {
                if (adjacencyListNode.getDestinationCity()->getCityCode() == route->getTo()) {
                    // 找到终点城市
                    // 遍历路线
                    for (Route* r : *adjacencyListNode.getRoutes()) {
                        // 检查路线是否存在
                        // 检查是否使用相同的交通工具
                        if (r->getVehicle()->getVehicleType() == route->getVehicle()->getVehicleType()) {
                            // 检查是否使用相同的交通工具型号
                            if (r->getVehicle()->getVehicleCode() == route->getVehicle()->getVehicleCode()) {
                                // 检查时间是否冲突
                                if (route->getDepartureTime().diffInMinutes(r->getDepartureTime()) >= 0) {
                                    if (route->getArrivalTime().diffInMinutes(r->getDepartureTime()) <= 0 ) {
                                        return true;
                                    }
                                } else {
                                    if (route->getDepartureTime().diffInMinutes(r->getArrivalTime()) >= 0) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

int AdjacencyList::addCity(City* city) {
    if (city == nullptr) {
        std::cout << "City is null" << std::endl;
        return ERROR;
    }

    // check if city already exists
    if (isCityExists(city)) {
        std::cout << "City " << city->getName() << "with code " << city->getCityCode() << " already exists" << std::endl;
        return ERROR;
    }

    if (citiesList == nullptr) {
        citiesList = new std::vector<City*>();
    }

    citiesList->push_back(city);

    // add city to adjacency list
    if (adjacencyList == nullptr) {
        adjacencyList = new std::vector<AdjacencyListPair>();
    }

    AdjacencyListPair* adjacencyListPair = new AdjacencyListPair();
    adjacencyListPair->setCity(city);
    adjacencyListPair->setNodes(new std::vector<AdjacencyListNode>());

    adjacencyList->push_back(*adjacencyListPair);

    numberOfCities++;

    return SUCCESS;
};

int AdjacencyList::deleteCity(int cityCode) {
    std::cout << "Deleting city with code " << cityCode << std::endl;
    // check if city exists
    if (citiesList == nullptr) {
        std::cout << "City list is empty" << std::endl;
        return ERROR;
    }

    // 检查城市是否存在
    for (std::vector<City*>::iterator it = citiesList->begin(); it != citiesList->end();) {
        City* city = *it;
        if ((city != nullptr) && (city->getCityCode() == cityCode)) {
            // 先删除邻接表中的城市
            for (std::vector<AdjacencyListPair>::iterator it1 = adjacencyList->begin(); it1 != adjacencyList->end();) {
                AdjacencyListPair pair = *it1;
                if (pair.getCity()->getCityCode() == cityCode) {
                    // 删除该pair中的所有routes(该city -> 其他城市的路线)
                    for (std::vector<AdjacencyListNode>::iterator it2 = pair.getNodes()->begin(); it2 != pair.getNodes()->end();) {
                        AdjacencyListNode node = *it2;
                        for (std::vector<Route*>::iterator it3 = node.getRoutes()->begin(); it3 != node.getRoutes()->end();) {
                            Route* route = *it3;
                            // // 删除routesList中的路线
                            // for (std::vector<Route*>::iterator it4 = routesList->begin(); it4 != routesList->end();) {
                            //     Route* r = *it4;
                            //     if (r->getRouteId() == route->getRouteId()) {
                            //         delete r;
                            //         r = nullptr;
                            //         it4 = routesList->erase(it4);
                            //         break;
                            //     } else {
                            //         it4++;
                            //     }
                            // }
                            delete route;
                            route = nullptr;
                            it3 = node.getRoutes()->erase(it3);
                            numberOfRoutes--;
                        }
                        node.getRoutes()->clear();
                        node.setRoutes(nullptr);
                        it2 = pair.getNodes()->erase(it2);
                    }
                    pair.getNodes()->clear();
                    pair.setNodes(nullptr);

                    // 删除该pair
                    it1 = adjacencyList->erase(it1);
                    break;
                } else {
                    it1++;
                }
            }

            // 删除其他城市到该城市的路线
            for (AdjacencyListPair pair : *adjacencyList) {
                for (AdjacencyListNode node : *pair.getNodes()) {
                    for (std::vector<Route*>::iterator it = node.getRoutes()->begin(); it != node.getRoutes()->end();) {
                        Route* route = *it;
                        if (route->getTo() == cityCode) {
                            // 删除routesList中的路线
                            // for (std::vector<Route*>::iterator it1 = routesList->begin(); it1 != routesList->end();) {
                            //     Route* r = *it1;
                            //     if (r->getTo() == cityCode) {
                            //         delete r;
                            //         r = nullptr;
                            //         it = routesList->erase(it);
                            //         break;
                            //     } else {
                            //         it++;
                            //     }
                            // }

                            delete route;
                            route = nullptr;
                            it = node.getRoutes()->erase(it);
                            numberOfRoutes--;
                        } else {
                            it++;
                        }
                    }
                }
            }

            delete city;
            city = nullptr;
            it = citiesList->erase(it);
            

            numberOfCities--;

            // 返回结果
            std::cout << "City deleted successfully" << std::endl;
            return SUCCESS;
        } else {
            it++;
        }
    }
    
    std::cout << "City not found" << std::endl;
    return ERROR;
}

int AdjacencyList::deleteRoute(int routeId, int from, int to) {
    // check if route exists
    // for (Route* route : *routesList) {
    //     if (route->getRouteId() == routeId) {
    //         // 获取该路线的起点和终点
    //         int from = route->getFrom();
    //         int to = route->getTo();

    //         // 删除邻接表中的路线
    //         for (AdjacencyListPair pair : *adjacencyList) {
    //             if (pair.getCity()->getCityCode() == from) {
    //                 for (AdjacencyListNode node : *pair.getNodes()) {
    //                     if (node.getDestinationCity()->getCityCode() == to) {
    //                         for (Route* r : *node.getRoutes()) {
    //                             if (r->getRouteId() == routeId) {
    //                                 delete r;
    //                                 r = nullptr;
    //                                 pair.getNodes()->erase(pair.getNodes()->begin());

    //                                 numberOfRoutes--;

    //                                 std::cout << "Route deleted successfully" << std::endl;
    //                                 return SUCCESS;
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    for (AdjacencyListPair pair : *adjacencyList) {
        if (pair.getCity()->getCityCode() == from) {
            for (AdjacencyListNode node : *pair.getNodes()) {
                if (node.getDestinationCity()->getCityCode() == to) {
                    for (std::vector<Route*>::iterator it = node.getRoutes()->begin(); it != node.getRoutes()->end();) {
                        Route* route = *it;
                        if (route->getRouteId() == routeId) {
                            delete route;
                            route = nullptr;
                            it = node.getRoutes()->erase(it);

                            numberOfRoutes--;

                            std::cout << "Route deleted successfully" << std::endl;
                            return SUCCESS;
                        } else {
                            it++;
                        }
                    }
                }
            }
        }
    }


    std::cout << "Route not found" << std::endl;
    return ERROR;
}

int AdjacencyList::addRoute(Route* route) {
    if (route == nullptr) {
        std::cout << "Route is null" << std::endl;
        return ERROR;
    }

    if (routesList == nullptr) {
        routesList = new std::vector<Route*>();
    }

    // check if route already exists
    if (isRouteExists(route)) {
        std::cout << "Route " << route->getFrom() << " -> " << route->getTo() << " already exists" << std::endl;
        return ERROR;
    }

    route->setRouteId(numberOfRoutes + 1);

    routesList->push_back(route);

    // add route to adjacency list
    // 查找起点城市
    for (AdjacencyListPair adjacencyListPair : *adjacencyList) {
        if (adjacencyListPair.getCity()->getCityCode() == route->getFrom()) { // 找到起点城市
            // 查找终点城市
            for (AdjacencyListNode adjacencyListNode : *adjacencyListPair.getNodes()) {
                if (adjacencyListNode.getDestinationCity()->getCityCode() == route->getTo()) { // 找到终点城市
                    // 添加路线
                    adjacencyListNode.getRoutes()->push_back(route);

                    std::cout << "Route added successfully" << std::endl;

                    numberOfRoutes++;

                    return SUCCESS;
                }
            }

            // 如果终点城市不存在, 则添加终点城市
            AdjacencyListNode* adjacencyListNode = new AdjacencyListNode();
            for (City* city : *citiesList) {
                if (city->getCityCode() == route->getTo()) {
                    adjacencyListNode->setDestinationCity(city);
                    break;
                }
            }

            adjacencyListNode->setRoutes(new std::vector<Route*>());
            adjacencyListNode->getRoutes()->push_back(route);

            adjacencyListPair.getNodes()->push_back(*adjacencyListNode);
            break;
        }
    }

    std::cout << "Route added successfully" << std::endl;

    numberOfRoutes++;

    return SUCCESS;
}

void AdjacencyList::displayAdjacencyList() {
    if (adjacencyList == nullptr) {
        printf("Adjacency list is empty\n");
        return;
    }

    // display info
    std::cout << "-------------------------------------------------------------------- " << std::endl;
    std::cout << "Number of cities: " << numberOfCities << std::endl;
    std::cout << "Number of routes: " << numberOfRoutes << std::endl;

    for (City* city : *citiesList) {
        std::cout << "City: " << city->getName() << " (" << city->getCityCode() << ")" << std::endl;
    }

    if (routesList == nullptr) {
        std::cout << "No routes found" << std::endl;
    } else {
        for (Route* route : *routesList) {
            std::cout << "Route: " << route->getFrom() << " -> " << route->getTo() << " (" << route->getDistance() << " km, " << route->getDuration() << " minutes, " << route->getCost() << " yuan " << route->getVehicle()->getVehicleCode() << ")" << std::endl;
        }
    } 

    std::cout << "--------------------------------" << std::endl;

    // display adjacency list
    for (AdjacencyListPair adjacencyListPair : *adjacencyList) {
        std::cout << "City: " << adjacencyListPair.getCity()->getName() << " (" << adjacencyListPair.getCity()->getCityCode() << ")" << std::endl;

        std::cout << "********************************" << std::endl;

        for (AdjacencyListNode adjacencyListNode : *adjacencyListPair.getNodes()) {
            std::cout << "Destination city: " << adjacencyListNode.getDestinationCity()->getName() << " (" << adjacencyListNode.getDestinationCity()->getCityCode() << ")" << std::endl;

            std::cout << "Routes:" << std::endl;

            for (Route* route : *adjacencyListNode.getRoutes()) {
                std::cout << "Route: " << "(" << route->getRouteId() << ") " <<
                route->getFrom() << " -> " << route->getTo() << " (" << route->getDistance() << " km, " << route->getDuration() << " minutes, " << route->getCost() << " yuan " << 
                "vehicle: " << "[" << route->getVehicle()->getVehicleType() << "] " <<
                route->getVehicle()->getVehicleCode() << 
                "[" << route->getDepartureTime().getHour() << ":" << route->getDepartureTime().getMinute() << " -> " << route->getArrivalTime().getHour() << ":" << route->getArrivalTime().getMinute() << "]" <<
                ")" << std::endl;
            }

            std::cout << "********************************" << std::endl;
        }

        
        std::cout << "--------------------------------" << std::endl;
    }
}

void AdjacencyList::dfsFindRoutes(int from, int to, int vehicleType, std::vector<std::vector<Route*>>& result, std::vector<Route*> currentRoute, std::unordered_set<int> visited, std::vector<AdjacencyListPair>* adjacencyList) {
    // 已经到达终点城市
    if (from == to) {
        result.push_back(currentRoute);
        return;
    }

    // 遍历邻接表
    for (AdjacencyListPair pair : *adjacencyList) {
        if (pair.getCity()->getCityCode() == from) {
            // 找到起点城市
            // 遍历该城市到其他城市的路线
            for (AdjacencyListNode node : *pair.getNodes()) {
                // 遍历每一个邻接城市节点
                for (Route* route : *node.getRoutes()) {
                    // 遍历每一条路线
                    // 判断是否是同一种交通工具
                    if (route->getVehicle()->getVehicleType() == vehicleType) {
                        // 判断是否已经访问过
                        if (visited.find(route->getTo()) == visited.end()) {
                            // 没有访问过
                            // 添加到当前路径
                            currentRoute.push_back(route);
                            visited.insert(route->getTo());
                            // 递归
                            dfsFindRoutes(route->getTo(), to, vehicleType, result, currentRoute, visited, adjacencyList);
                            // 回溯
                            currentRoute.pop_back();
                            visited.erase(route->getTo());
                        }
                    }
                }
            }
        }
    }
}

int AdjacencyList::findAllRoutes(int from, int to, int vehicleType, std::vector<std::vector<Route*>>& result) {
    std::vector<Route*> currentRoute;
    std::unordered_set<int> visited;

    dfsFindRoutes(from, to, vehicleType, result, currentRoute, visited, adjacencyList);

    // 输出结果
    std::cout << "From " << from << " to " << to << " by " << vehicleType << std::endl;
    std::cout << "All routes: " << std::endl;

    for (std::vector<Route*> routes : result) {
        for (Route* route : routes) {
            std::cout << route->getFrom() << " -> ";
        }
        std::cout << to << std::endl;
    }

    return SUCCESS;
}

// 最快到达算法
int AdjacencyList::mostFastestWay(int from, int to, int vehicleType) {
    // 最快到达算法（以时间为权重）
    // 使用 Dijkstra 算法

    // 定义一个从记录从起点到每个城市的最短时间
    std::unordered_map<int, long> recordTable; // 记录到达每个城市的最短时间
    // 将每个值初始化为无穷大
    for (City* city : *citiesList) {
        recordTable[city->getCityCode()] = std::numeric_limits<long>::max();
    }
    // 起点时间为 0
    recordTable[from] = 0;

    // 定义一个优先队列 （定义为 <时间, 城市>）
    std::priority_queue<std::pair<long, int>, std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> pq;
    pq.push(std::make_pair(0, from));

    // 定义一个记录路径的表 (key: cityCode, value: previous cityCode)
    std::unordered_map<int, int> pathTable;

    // 开始遍历
    while (!pq.empty()) {
        // 取出队列中的第一个元素
        std::pair<long, int> top = pq.top();
        pq.pop();

        // 取出城市编号
        int cityCode = top.second;
        // 取出时间
        long time = top.first;

        // 如果已经访问过该城市，则跳过
        if (recordTable[cityCode] < time) { // 如果访问时间小于当前时间，则跳过
            continue;
        }

        // 遍历邻接表
        for (AdjacencyListPair pair : *adjacencyList) {
            if (pair.getCity()->getCityCode() == cityCode) { // 找到起点城市
                // 遍历该城市到其他城市的路线
                for (AdjacencyListNode node : *pair.getNodes()) {
                    // 遍历每一个邻接城市节点
                    for (Route* route : *node.getRoutes()) {
                        // 遍历每一条路线
                        // 判断是否是同一种交通工具
                        if (route->getVehicle()->getVehicleType() == vehicleType) {
                            // 判断是否是最短时间
                            if (time + route->getDuration() < recordTable[route->getTo()]) {
                                recordTable[route->getTo()] = time + route->getDuration();
                                pq.push(std::make_pair(time + route->getDuration(), route->getTo()));
                                pathTable[route->getTo()] = cityCode;
                            }
                        }
                    }
                }
            }
        }
    }

    // 判断是否可达
    if (recordTable[to] == std::numeric_limits<long>::max()) {
        std::cout << "No way to reach" << std::endl;
        return ERROR;
    }

    // 输出结果
    std::cout << "From " << from << " to " << to << " by " << vehicleType << std::endl;

    std::cout << "The fastest way is: " << std::endl;
    std::cout << "Time: " << recordTable[to] << " minutes" << std::endl;

    // 回溯路径
    std::vector<int> path;
    int currentCity = to;
    while (currentCity != from) {
        path.push_back(currentCity);
        currentCity = pathTable[currentCity];
    }
    path.push_back(from);
    // 反转路径
    std::reverse(path.begin(), path.end());

    // 输出路径
    std::cout << "Path: ";
    for (int cityCode : path) {
        std::cout << cityCode << " -> ";
    }
    std::cout << std::endl;

    return SUCCESS;
}

int AdjacencyList::mostEconomicWay(int from, int to, int vehicleType) {
    // 最省钱到达算法（以费用为权重）
    // 使用 Dijkstra 算法

    // 定义一个从记录从起点到每个城市的最短费用
    std::unordered_map<int, long> recordTable; // 记录到达每个城市的最短费用
    // 将每个值初始化为无穷大
    for (City* city : *citiesList) {
        recordTable[city->getCityCode()] = std::numeric_limits<long>::max();
    }   

    // 起点费用为 0
    recordTable[from] = 0;

    // 定义一个优先队列 （定义为 <费用, 城市>）
    std::priority_queue<std::pair<long, int>, std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> pq;
    pq.push(std::make_pair(0, from));

    // 定义一个记录路径的表 (key: cityCode, value: previous cityCode)
    std::unordered_map<int, int> pathTable;

    // 开始遍历
    while (!pq.empty()) {
        // 取出队列中的第一个元素
        std::pair<long, int> top = pq.top();
        pq.pop();

        // 取出城市编号
        int cityCode = top.second;
        // 取出费用
        long cost = top.first;

        // 如果已经访问过该城市，则跳过
        if (recordTable[cityCode] < cost) { // 如果访问费用小于当前费用，则跳过
            continue;
        }

        // 遍历邻接表
        for (AdjacencyListPair pair : *adjacencyList) {
            if (pair.getCity()->getCityCode() == cityCode) { // 找到起点城市
                // 遍历该城市到其他城市的路线
                for (AdjacencyListNode node : *pair.getNodes()) {
                    // 遍历每一个邻接城市节点
                    for (Route* route : *node.getRoutes()) {
                        // 遍历每一条路线
                        // 判断是否是同一种交通工具
                        if (route->getVehicle()->getVehicleType() == vehicleType) {
                            // 判断是否是最短费用
                            if (cost + route->getCost() < recordTable[route->getTo()]) {
                                recordTable[route->getTo()] = cost + route->getCost();
                                pq.push(std::make_pair(cost + route->getCost(), route->getTo()));
                                pathTable[route->getTo()] = cityCode;
                            }
                        }
                    }
                }
            }
        }
    }

    // 判断是否可达
    if (recordTable[to] == std::numeric_limits<long>::max()) {
        std::cout << "No way to reach" << std::endl;
        return ERROR;
    }

    // 回溯路径
    std::vector<int> path;
    int currentCity = to;
    while (currentCity != from) {
        path.push_back(currentCity);
        currentCity = pathTable[currentCity];
    }
    path.push_back(from);

    // 反转路径
    std::reverse(path.begin(), path.end());

    // 输出结果
    std::cout << "From " << from << " to " << to << " by " << vehicleType << std::endl;

    std::cout << "The most economic way is: " << std::endl;
    std::cout << "Cost: " << recordTable[to] << " yuan" << std::endl;

    // 输出路径
    std::cout << "Path: ";
    for (int cityCode : path) {
        std::cout << cityCode << " -> ";
    }
    std::cout << std::endl;

    return SUCCESS;
}

