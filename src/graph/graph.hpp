#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <tuple>
#include <algorithm>


#include "graph.h"

int AdjacencyList::getNumberOfRoutes() {
    if (adjacencyList == nullptr) {
        return 0;
    }

    int count = 0;

    for (AdjacencyListPair pair : *adjacencyList) {
        for (AdjacencyListNode node : *pair.getNodes()) {
            count += node.getRoutes()->size();
        }
    }

    return count;
}

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
                            delete route;
                            route = nullptr;
                            it3 = node.getRoutes()->erase(it3);
                            // numberOfRoutes--;
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
                            delete route;
                            route = nullptr;
                            it = node.getRoutes()->erase(it);
                            // numberOfRoutes--;
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

                            // numberOfRoutes--;

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

    // check if route already exists
    if (isRouteExists(route)) {
        std::cout << "Route " << route->getFrom() << " -> " << route->getTo() << " already exists" << std::endl;
        return ERROR;
    }

    // 设置routeid
    route->setRouteId(numberOfRoutes+1);

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


void AdjacencyList::dfsFindRoutes(
    int from,
    int to,
    int vehicleType,
    std::vector<std::vector<Route*>>& result,
    std::vector<Route*> currentRoute,
    std::unordered_set<int> visited,
    std::vector<AdjacencyListPair>* adjacencyList,
    Time previousArrivalTime) {

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
                        // 判断时间是否合理（当前路线的出发时间是否晚于上一条路线的到达时间）
                        if (previousArrivalTime.diffInMinutes(route->getDepartureTime()) >= 0) {
                            // 添加到当前路径
                            currentRoute.push_back(route);
                            visited.insert(route->getTo());
                            // 递归
                            dfsFindRoutes(route->getTo(), to, vehicleType, result, currentRoute, visited, adjacencyList, route->getArrivalTime());
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

    dfsFindRoutes(from, to, vehicleType, result, currentRoute, visited, adjacencyList, Time(0, 0));

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
int AdjacencyList::mostFastestWay(int from, int to, int vehicleType, std::vector<Route*>& result) {
    // 最快到达算法（以时间为权重） 
    // 使用 Dijkstra 算法
    // 考虑时间的合理性和两天路线之间的时间间隔，即等待时间

    // 定义一个从记录从起点到每个城市的最短时间
    std::unordered_map<int, long> recordTable; // 记录到达每个城市的最短时间
    // 将每个值初始化为无穷大
    for (City* city : *citiesList) {
        recordTable[city->getCityCode()] = std::numeric_limits<long>::max();
    }
    // 起点时间为 0
    recordTable[from] = 0;

    // 定义一个优先队列 （定义为 <时间, 城市, 到达时间, 路线指针>）
    std::priority_queue<std::tuple<long, int, Time, Route*>, 
                        std::vector<std::tuple<long, int, Time, Route*>>, 
                        std::greater<>> pq;

    pq.push(std::make_tuple(0, from, Time(0, 0) , nullptr));

    // 路径表：记录到达每个城市的路线指针
    std::unordered_map<int, Route*> routeTable;

    while(!pq.empty()) {
        auto [time, cityCode, arrivalTime, route] = pq.top();
        pq.pop();

        // 如果当前时间已经大于记录的时间，则跳过
        if (recordTable[cityCode] < time) {
            continue;
        }

        // 遍历邻接表
        for (AdjacencyListPair pair : *adjacencyList) {
            if (pair.getCity()->getCityCode() == cityCode) {
                // 找到起点城市
                for (AdjacencyListNode node : *pair.getNodes()) {
                    for (Route* route : *node.getRoutes()) {
                        if (route->getVehicle()->getVehicleType() == vehicleType) { // 判断是否是同一种交通工具
                            // 判断时间是否合理（当前路线的出发时间是否晚于上一条路线的到达时间）
                            if (route->getDepartureTime().diffInMinutes(arrivalTime) <= 0) {
                                // 判断是否是最短时间 (考虑等待时间,即前一条route的到达时间和当前route的出发时间之间的间隔)
                                if ((time + route->getDuration() + arrivalTime.diffInMinutes(route->getDepartureTime())) < recordTable[route->getTo()]) {
                                    recordTable[route->getTo()] = time + route->getDuration() + arrivalTime.diffInMinutes(route->getDepartureTime());
                                    int waitHours = (arrivalTime.diffInMinutes(route->getDepartureTime())) / 60;
                                    int waitMinutes = (arrivalTime.diffInMinutes(route->getDepartureTime())) % 60;
                                    pq.push(std::make_tuple(time + route->getDuration() + arrivalTime.diffInMinutes(route->getDepartureTime()), route->getTo(), route->getArrivalTime(), route));
                                    routeTable[route->getTo()] = route;
                                }
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
    int currentCity = to;
    while (currentCity != from) {
        if (routeTable.find(currentCity) == routeTable.end()) {
            std::cout << "No way to reach" << std::endl;
            return ERROR;
        }
        result.push_back(routeTable[currentCity]);
        currentCity = routeTable[currentCity]->getFrom();
    }

    // 最终时间减掉起始时间
    long startTimeinMinutes = (*result.begin())->getDepartureTime().getHour() * 60 + (*result.begin())->getDepartureTime().getMinute();
    recordTable[to] -= startTimeinMinutes;

    // 反转路径
    std::reverse(result.begin(), result.end());

    // 输出结果
    std::cout << "From " << from << " to " << to << " by " << vehicleType << std::endl;
    std::cout << "The most fastest way is: " << std::endl;
    std::cout << "Time: " << recordTable[to] << " minutes" << std::endl;

    // 输出路径
    std::cout << "Path: ";
    for (Route* route : result) {
        std::cout << route->getFrom() << "(routeid: " << route->getRouteId() << ") -> ";
    }
    std::cout << to << std::endl;

    return SUCCESS;
}

int AdjacencyList::mostEconomicWay(int from, int to, int vehicleType, std::vector<Route*>& result) {
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

    // 定义一个优先队列 （定义为 <花费, 城市, 到达时间, 路线指针>)
    std::priority_queue<std::tuple<long, int, Time, Route*>,
                        std::vector<std::tuple<long, int, Time, Route*>>,
                        std::greater<>> pq;

    pq.push(std::make_tuple(0, from, Time(0, 0), nullptr));

    // 路径表：记录到达每个城市的路线指针
    std::unordered_map<int, Route*> routeTable;

    while (!pq.empty()) {
        auto [cost, cityCode, arrivalTime, route] = pq.top();
        pq.pop();

        // 如果当前费用已经大于记录的费用，则跳过
        if (recordTable[cityCode] < cost) {
            continue;
        }

        // 遍历邻接表
        for (AdjacencyListPair pair : *adjacencyList) {
            if (pair.getCity()->getCityCode() == cityCode) {
                // 找到起点城市
                for (AdjacencyListNode node : *pair.getNodes()) {
                    for (Route* route : *node.getRoutes()) {
                        if (route->getVehicle()->getVehicleType() == vehicleType) { // 判断是否是同一种交通工具
                            // 判断时间是否合理（当前路线的出发时间是否晚于上一条路线的到达时间）
                            if (arrivalTime.diffInMinutes(route->getDepartureTime()) >= 0) {
                                // 判断是否是最短费用
                                if (cost + route->getCost() < recordTable[route->getTo()]) {
                                    recordTable[route->getTo()] = cost + route->getCost();
                                    pq.push(std::make_tuple(cost + route->getCost(), route->getTo(), route->getArrivalTime(), route));
                                    routeTable[route->getTo()] = route;
                                }
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
    int currentCity = to;
    while (currentCity != from) {
        if (routeTable.find(currentCity) == routeTable.end()) {
            std::cout << "No way to reach" << std::endl;
            return ERROR;
        }
        result.push_back(routeTable[currentCity]);
        currentCity = routeTable[currentCity]->getFrom();
    }

    // 反转路径
    std::reverse(result.begin(), result.end());

    // 输出结果
    std::cout << "From " << from << " to " << to << " by " << vehicleType << std::endl;
    std::cout << "The most economic way is: " << std::endl;
    std::cout << "Cost: " << recordTable[to] << " yuan" << std::endl;

    // 输出路径
    std::cout << "Path: ";
    for (Route* route : result) {
        std::cout << route->getFrom() << "(routeid: " << route->getRouteId() << ") -> ";
    }

    return SUCCESS;
}

