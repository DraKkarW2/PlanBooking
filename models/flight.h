#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>
#include "sqlconnect.h"

class flight {
private:
    int id;
    int capacity;
    std::string flight_number;
    int plane_id;

public:
    flight(const std::string& flight_number, int capacity, int plane_id, sqlconnect& db);
    flight(int id, const std::string& flight_number, int capacity, int plane_id);

    // ************************************* Getters ************************************* //
    int getId() const;
    int getCapacity() const;
    std::string getFlightNumber() const;
    int getPlaneId() const;
    
    // ************************************* Setters ************************************* //
    void setCapacity(int capacity);
    void setFlightNumber(const std::string& flight_number);
    void setPlaneId(int plane_id);


    void updateInDB(sqlconnect& db);
    void deleteFromDB(sqlconnect& db);

    // ************************************* static methods ************************************* // 
    static flight getById(int id, sqlconnect& db);
    static std::vector<flight> getAllFlights(sqlconnect& db);
    static void deleteById(int id, sqlconnect& db);
};

#endif