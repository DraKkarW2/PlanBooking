#include "plane.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <mysql/mysql.h> // pour MYSQL_ROW

// constructor database
plane::plane(std::string number, time_t departure_time, int capacity, sqlconnect& db)
    : number(number), departure_time(departure_time), capacity(capacity)
{
    std::stringstream query;
    query << "INSERT INTO plane(number, capacity, departure_time) VALUES ('"
          << number << "', " << capacity << ", " << departure_time << ")";
    db.execute(query.str());

    std::stringstream selectQuery;
    selectQuery << "SELECT id FROM plane WHERE number='" << number 
                << "' AND departure_time=" << departure_time 
                << " ORDER BY id DESC LIMIT 1";
    MYSQL_RES* res = db.execute(selectQuery.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        this->id = row ? std::stoi(row[0]) : -1;
        mysql_free_result(res);
    } else {
        this->id = -1;
    }

    std::cout << "Plane created with id " << this->id << std::endl;
}
// simple constructor
plane::plane(int id, std::string number, time_t departure_time, int capacity)
    : id(id), number(number), departure_time(departure_time), capacity(capacity) {}

// ************************************* Getters ************************************* //
int plane::getId() const { return id; }
std::string plane::getNumber() const { return number; }
time_t plane::getDepartureTime() const { return departure_time; }
int plane::getCapacity() const { return capacity; }
// ************************************* Setters ************************************* //
void plane::setNumber(const std::string& number) { this->number = number; }
void plane::setDepartureTime(time_t departure_time) { this->departure_time = departure_time; }
void plane::setCapacity(int capacity) { this->capacity = capacity; }

void plane::updateInDB(sqlconnect& db) {
    std::stringstream query;
    query << "UPDATE plane SET number='" << number
          << "', capacity=" << capacity
          << ", departure_time=" << departure_time
          << " WHERE id=" << id;
    db.execute(query.str());
}

void plane::deleteFromDB(sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM plane WHERE id=" << id;
    db.execute(query.str());
}
// ************************************* static methods ************************************* // 
plane plane::getById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "SELECT number, capacity, departure_time FROM plane WHERE id=" << id;
    MYSQL_RES* res = db.execute(query.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            plane p(id, row[0], std::stol(row[2]), std::stoi(row[1]));
            mysql_free_result(res);
            return p;
        }
        mysql_free_result(res);
    }
    return plane(-1, "", 0, 0);
}

plane plane::getByNumber(const std::string& number, sqlconnect& db) {
    std::stringstream query;
    query << "SELECT id, capacity, departure_time FROM plane WHERE number='" << number << "'";
    MYSQL_RES* res = db.execute(query.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            plane p(std::stoi(row[0]), number, std::stol(row[2]), std::stoi(row[1]));
            mysql_free_result(res);
            return p;
        }
        mysql_free_result(res);
    }
    return plane(-1, "", 0, 0);
}

std::vector<plane> plane::getAllPlanes(sqlconnect& db) {
    std::vector<plane> planes;
    std::string query = "SELECT id, number, capacity, departure_time FROM plane";
    MYSQL_RES* res = db.execute(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            planes.emplace_back(
                std::stoi(row[0]),
                row[1],
                std::stol(row[3]),
                std::stoi(row[2])
            );
        }
        mysql_free_result(res);
    }
    return planes;
}


void plane::deleteById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM plane WHERE id=" << id;
    db.execute(query.str());
}