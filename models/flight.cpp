#include "flight.h"
#include <iostream>
#include <sstream>
#include <mysql/mysql.h>

// constructor database
flight::flight(const std::string& flight_number, int capacity, int plane_id, sqlconnect& db)
    : flight_number(flight_number), capacity(capacity), plane_id(plane_id)
{
    // check plane exist
    std::stringstream planeCheck;
    planeCheck << "SELECT id FROM plane WHERE id=" << plane_id;
    std::cout << planeCheck.str() << std::endl;
    MYSQL_RES* resPlane = db.execute(planeCheck.str());
    if (!resPlane || mysql_num_rows(resPlane) == 0) {
        if(resPlane) mysql_free_result(resPlane);
        throw std::runtime_error("Erreur: l'avion avec l'id " + std::to_string(plane_id) + " n'existe pas.");
    }
    mysql_free_result(resPlane);
    // insert to database
    std::stringstream query;
    query << "INSERT INTO flight(flight_number, capacity, plane_id) VALUES ('"
          << flight_number << "', " << capacity << ", " << plane_id << ")";
    db.execute(query.str());
    // get id auto_incremented
    std::stringstream selectQuery;
    selectQuery << "SELECT id FROM flight WHERE flight_number='" << flight_number
                << "' AND plane_id=" << plane_id
                << " ORDER BY id DESC LIMIT 1";
    MYSQL_RES* res = db.execute(selectQuery.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        this->id = row ? std::stoi(row[0]) : -1;
        mysql_free_result(res);
    } else {
        this->id = -1;
    }

    std::cout << "Flight created with id " << this->id << std::endl;
}

// simple constructor
flight::flight(int id, const std::string& flight_number, int capacity, int plane_id)
    : id(id), flight_number(flight_number), capacity(capacity), plane_id(plane_id) {}

// ************************************* Getters ************************************* //
int flight::getId() const { return id; }
int flight::getCapacity() const { return capacity; }
std::string flight::getFlightNumber() const { return flight_number; }
int flight::getPlaneId() const { return plane_id; }

// ************************************* Setters ************************************* //
void flight::setCapacity(int capacity) { this->capacity = capacity; }
void flight::setFlightNumber(const std::string& flight_number) { this->flight_number = flight_number; }
void flight::setPlaneId(int plane_id) { this->plane_id = plane_id; }


void flight::updateInDB(sqlconnect& db) {
    std::stringstream query;
    query << "UPDATE flight SET flight_number='" << flight_number
          << "', capacity=" << capacity
          << ", plane_id=" << plane_id
          << " WHERE id=" << id;
    db.execute(query.str());
}

void flight::deleteFromDB(sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM flight WHERE id=" << id;
    db.execute(query.str());
}

// ************************************* static methods ************************************* // 
flight flight::getById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "SELECT flight_number, capacity, plane_id FROM flight WHERE id=" << id;
    MYSQL_RES* res = db.execute(query.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            flight f(id, row[0], std::stoi(row[1]), std::stoi(row[2]));
            mysql_free_result(res);
            return f;
        }
        mysql_free_result(res);
    }
    return flight(-1, "", 0, 0);
}

std::vector<flight> flight::getAllFlights(sqlconnect& db) {
    std::vector<flight> all;
    std::string query = "SELECT id, flight_number, capacity, plane_id FROM flight";
    MYSQL_RES* res = db.execute(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            all.emplace_back(std::stoi(row[0]), row[1], std::stoi(row[2]), std::stoi(row[3]));
        }
        mysql_free_result(res);
    }
    return all;
}

void flight::deleteById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM flight WHERE id=" << id;
    db.execute(query.str());
}