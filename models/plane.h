#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <ctime>
#include "sqlconnect.h"

class plane {
private:
    int id;
    std::string number;
    time_t departure_time;
    int capacity;

public:
    plane(std::string number, time_t departure_time, int capacity, sqlconnect& db);
    int getId();
    std::string getNumber();
    int getCapacity();
};

#endif