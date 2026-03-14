#include "booking.h"
#include <iostream>
#include <sstream>
#include <mysql/mysql.h>
// constructor database
booking::booking(double price, time_t date, int flight_id, int passenger_id, sqlconnect& db)
    : price(price), date(date), flight_id(flight_id), passenger_id(passenger_id)
{
    // check flight exist
    std::stringstream flightCheck;
    flightCheck << "SELECT id FROM flight WHERE id=" << flight_id;
    MYSQL_RES* resFlight = db.execute(flightCheck.str());
    if (!resFlight || mysql_num_rows(resFlight) == 0) {
        if(resFlight) mysql_free_result(resFlight);
        throw std::runtime_error("Erreur: le vol avec l'id " + std::to_string(flight_id) + " n'existe pas.");
    }
    mysql_free_result(resFlight);

    // check passenger exist
    std::stringstream passengerCheck;
    passengerCheck << "SELECT id FROM passengers WHERE id=" << passenger_id;
    MYSQL_RES* resPassenger = db.execute(passengerCheck.str());
    if (!resPassenger || mysql_num_rows(resPassenger) == 0) {
        if(resPassenger) mysql_free_result(resPassenger);
        throw std::runtime_error("Erreur: le passager avec l'id " + std::to_string(passenger_id) + " n'existe pas.");
    }
    mysql_free_result(resPassenger);

    // insert to database
    std::stringstream query;
    query << "INSERT INTO booking(price, date, flight_id, passenger_id) VALUES ("
          << price << ", " << date << ", " << flight_id << ", " << passenger_id << ")";
    db.execute(query.str());

    std::stringstream selectQuery;
    selectQuery << "SELECT id FROM booking WHERE flight_id=" << flight_id
                << " AND passenger_id=" << passenger_id
                << " ORDER BY id DESC LIMIT 1";
    MYSQL_RES* res = db.execute(selectQuery.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        this->id = row ? std::stoi(row[0]) : -1;
        mysql_free_result(res);
    } else {
        this->id = -1;
    }

    std::cout << "Booking created with id " << this->id << std::endl;
}


booking::booking(int id, double price, time_t date, int flight_id, int passenger_id)
    : id(id), price(price), date(date), flight_id(flight_id), passenger_id(passenger_id) {}

// ************************************* Getters ************************************* //
int booking::getId() const { return id; }
double booking::getPrice() const { return price; }
time_t booking::getDate() const { return date; }
int booking::getFlightId() const { return flight_id; }
int booking::getPassengerId() const { return passenger_id; }

// ************************************* Setters ************************************* //
void booking::setPrice(double price) { this->price = price; }
void booking::setDate(time_t date) { this->date = date; }
void booking::setFlightId(int flight_id) { this->flight_id = flight_id; }
void booking::setPassengerId(int passenger_id) { this->passenger_id = passenger_id; }


void booking::updateInDB(sqlconnect& db) {
    std::stringstream query;
    query << "UPDATE booking SET price=" << price
          << ", date=" << date
          << ", flight_id=" << flight_id
          << ", passenger_id=" << passenger_id
          << " WHERE id=" << id;
    db.execute(query.str());
}

void booking::deleteFromDB(sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM booking WHERE id=" << id;
    db.execute(query.str());
}

// ************************************* static methods ************************************* //
booking booking::getById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "SELECT price, date, flight_id, passenger_id FROM booking WHERE id=" << id;
    MYSQL_RES* res = db.execute(query.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            booking b(id, std::stod(row[0]), std::stol(row[1]), std::stoi(row[2]), std::stoi(row[3]));
            mysql_free_result(res);
            return b;
        }
        mysql_free_result(res);
    }
    return booking(-1, 0, 0, 0, 0);
}

std::vector<booking> booking::getAllBookings(sqlconnect& db) {
    std::vector<booking> all;
    std::string query = "SELECT id, price, date, flight_id, passenger_id FROM booking";
    MYSQL_RES* res = db.execute(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            all.emplace_back(std::stoi(row[0]), std::stod(row[1]), std::stol(row[2]), std::stoi(row[3]), std::stoi(row[4]));
        }
        mysql_free_result(res);
    }
    return all;
}

void booking::deleteById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM booking WHERE id=" << id;
    db.execute(query.str());
}