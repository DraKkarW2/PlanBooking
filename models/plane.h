#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <vector>
#include <ctime>
#include "sqlconnect.h"

class plane {
private:
    int id;
    std::string number;
    time_t departure_time;
    int capacity;

public:
    // constructor avec insert bdd
    plane(std::string number, time_t departure_time, int capacity, sqlconnect& db);
    // constructor sans insert bdd
    plane(int id, std::string number, time_t departure_time, int capacity);

    // ************************************* Getters ************************************* //
    int getId() const;
    std::string getNumber() const;
    time_t getDepartureTime() const;
    int getCapacity() const;
    // ************************************* Setters ************************************* //
    void setNumber(const std::string& number);
    void setDepartureTime(time_t departure_time);
    void setCapacity(int capacity);


    void updateInDB(sqlconnect& db);  
    void deleteFromDB(sqlconnect& db); 
    // ************************************* static methods ************************************* // 
    static plane getById(int id, sqlconnect& db);
    static plane getByNumber(const std::string& number, sqlconnect& db);
    static std::vector<plane> getAllPlanes(sqlconnect& db);
    static void deleteById(int id, sqlconnect& db);
};

#endif