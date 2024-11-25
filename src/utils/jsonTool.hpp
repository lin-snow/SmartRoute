#pragma once

#include <string>
#include "nlohmann/json.hpp"

#include "../module/module.h"
#include "../system/system.h"

nlohmann::json System::city2json(City* city) {
    nlohmann::json cityJson;
    cityJson["name"] = city->getName();
    cityJson["cityCode"] = city->getCityCode();

    return cityJson;
}

nlohmann::json System::route2json(Route* route) {
    nlohmann::json routeJson;
    routeJson["from"] = route->getFrom();
    routeJson["to"] = route->getTo();
    routeJson["distance"] = route->getDistance();
    routeJson["duration"] = route->getDuration();
    routeJson["cost"] = route->getCost();
    routeJson["vehicleType"] = route->getVehicle()->getVehicleType();
    routeJson["vehicleCode"] = route->getVehicle()->getVehicleCode();
    routeJson["departureTime"] = route->getDepartureTime().getTimeStamp();
    routeJson["arrivalTime"] = route->getArrivalTime().getTimeStamp();

    return routeJson;
}

City* System::json2city(nlohmann::json cityJson) {
    return new City(cityJson["name"], cityJson["cityCode"]);
}

Route* System::json2route(nlohmann::json routeJson) {
    return new Route(routeJson["from"], routeJson["to"], routeJson["distance"], routeJson["duration"], new Vehicle((VehicleType)routeJson["vehicleType"], routeJson["vehicleCode"]), Time(routeJson["departureTime"]), Time(routeJson["arrivalTime"]), routeJson["cost"]);
}