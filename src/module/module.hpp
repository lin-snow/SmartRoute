#pragma once

#include "module.h"

Time::Time() {
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
}

Time::Time(int year, int month, int day, int hour, int minute) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
}

long Time::diffInMinutes(const Time &t) const {
    long diff = 0;
    diff += (t.year - year) * 365 * 24 * 60;
    diff += (t.month - month) * 30 * 24 * 60;
    diff += (t.day - day) * 24 * 60;
    diff += (t.hour - hour) * 60;
    diff += t.minute - minute;
    return diff;
}

std::string Time::getTimeStamp() const {
    std::string timeStamp =
        (year < 10 ? "000" : year < 100 ? "00" : year < 1000 ? "0" : "") + std::to_string(year) + "-" +
        (month < 10 ? "0" : "") + std::to_string(month) + "-" +
        (day < 10 ? "0" : "") + std::to_string(day) + " " +
        (hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
        (minute < 10 ? "0" : "") + std::to_string(minute);

    return timeStamp;
}

City::City(const std::string &name, int cityCode) {
    this->name = name;
    this->cityCode = cityCode;
}

Vehicle::Vehicle(VehicleType vehicleType, const std::string &vehicleCode) {
    this->vehicleType = vehicleType;
    this->vehicleCode = vehicleCode;
}

Route::Route(int from, int to, long distance, long duration, Vehicle* vehicle, const Time &departureTime, const Time &arrivalTime, long cost) {
    this->from = from;
    this->to = to;
    this->distance = distance;
    this->duration = duration;
    this->vehicle = vehicle;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->cost = cost;
}




