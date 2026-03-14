#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <ctime>
#include "sqlconnect.h"

class booking {
private:
    int id;
    double price;
    time_t date;
    int flight_id;
    int passenger_id;

public:
    booking(double price, time_t date, int flight_id, int passenger_id, sqlconnect& db);

    booking(int id, double price, time_t date, int flight_id, int passenger_id);

    // ************************************* Getters ************************************* //

    int getId() const;
    double getPrice() const;
    time_t getDate() const;
    int getFlightId() const;
    int getPassengerId() const;

    // ************************************* Setters ************************************* //
    void setPrice(double price);
    void setDate(time_t date);
    void setFlightId(int flight_id);
    void setPassengerId(int passenger_id);

    void updateInDB(sqlconnect& db);
    void deleteFromDB(sqlconnect& db);
    // ************************************* static methods ************************************* //
    static booking getById(int id, sqlconnect& db);
    static std::vector<booking> getAllBookings(sqlconnect& db);
    static void deleteById(int id, sqlconnect& db);
};

#endif