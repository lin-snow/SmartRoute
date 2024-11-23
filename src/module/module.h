#pragma once

#include <string>

#include "../graph/graph.h"

enum class VehicleType {
    TRAIN = 0,
    PLAIN = 1
};

class Time {
    public:
        Time();
        Time(int year, int month, int day, int hour, int minute);

        // setters
        void setYear(int year) { this->year = year; }
        void setMonth(int month) { this->month = month; }
        void setDay(int day) { this->day = day; }
        void setHour(int hour) { this->hour = hour; }
        void setMinute(int minute) { this->minute = minute; }

        // getters
        int getYear() const { return year; }
        int getMonth() const { return month; }
        int getDay() const { return day; }
        int getHour() const { return hour; }
        int getMinute() const { return minute; }

        // methods
        long diffInMinutes(const Time &t) const; // difference in minutes
        std::string getTimeStamp() const; // "2024-01-01 00:00"

    private:
        int year; // 2024
        int month; // 1-12
        int day; // 1-31
        int hour; // 0-23
        int minute; // 0-59
};

class City {
    public: 
        City(const std::string &name, int cityCode);
        
        // setters and getters
        std::string getName() const { return name; }
        void setName(const std::string &name) { this->name = name; }

        int getCityCode() const { return cityCode; }
        void setCityCode(int cityCode) { this->cityCode = cityCode; }

    private:
        std::string name; // city name
        int cityCode; // city code
};

class Vehicle {
    public:
        Vehicle(VehicleType vehicleType, const std::string &vehicleCode);

        // setters and getters
        VehicleType getVehicleType() const { return vehicleType; }
        void setVehicleType(VehicleType vehicleType) { this->vehicleType = vehicleType; }

        std::string getVehicleCode() const { return vehicleCode; }
        void setVehicleCode(const std::string &vehicleCode) { this->vehicleCode = vehicleCode; }

    private:
        VehicleType vehicleType; // BUS or TRAIN
        std::string vehicleCode; // 型号 e.g. "G1234"
};

class Route {
    public:
        Route(int from, int to, long distance, long duration, Vehicle* vehicle, const Time &departureTime, const Time &arrivalTime, long cost);

        // getters and setters
        int getFrom() const { return from; }
        void setFrom(int from) { this->from = from; }

        int getTo() const { return to; }
        void setTo(int to) { this->to = to; }

        long getDistance() const { return distance; }
        void setDistance(long distance) { this->distance = distance; }

        long getDuration() const { return duration; }
        void setDuration(long duration) { this->duration = duration; }

        Vehicle* getVehicle() const { return vehicle; }
        void setVehicle(Vehicle* vehicle) { this->vehicle = vehicle; }

        Time getDepartureTime() const { return departureTime; }
        void setDepartureTime(const Time &departureTime) { this->departureTime = departureTime; }

        Time getArrivalTime() const { return arrivalTime; }
        void setArrivalTime(const Time &arrivalTime) { this->arrivalTime = arrivalTime; }

        long getCost() const { return cost; }
        void setCost(long cost) { this->cost = cost; }

    private:
        int from; // cityCode of the starting city
        int to; // cityCode of the destination city
        long distance; // in meters (m)
        long duration; // in minutes (m)
        Vehicle* vehicle; // vehicle used
        Time departureTime; // departure time
        Time arrivalTime; // arrival time
        long cost; // cost ￥
};

#include "./module.hpp"  