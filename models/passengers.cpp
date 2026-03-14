#include "passengers.h"
#include <iostream>
#include <sstream>
#include <mysql/mysql.h> 

// constructor database
passengers::passengers(const std::string& name, const std::string& passportNumber, sqlconnect& db)
    : name(name), passportNumber(passportNumber)
{
    std::stringstream query;
    query << "INSERT INTO passengers(name, passportNumber) VALUES ('"
          << name << "', '" << passportNumber << "')";
    db.execute(query.str());

    std::stringstream selectQuery;
    selectQuery << "SELECT id FROM passengers WHERE name='" << name
                << "' AND passportNumber='" << passportNumber
                << "' ORDER BY id DESC LIMIT 1";
    MYSQL_RES* res = db.execute(selectQuery.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        this->id = row ? std::stoi(row[0]) : -1;
        mysql_free_result(res);
    } else {
        this->id = -1;
    }

    std::cout << "Passenger created with id " << this->id << std::endl;
}
// simple constructor
passengers::passengers(int id, const std::string& name, const std::string& passportNumber)
    : id(id), name(name), passportNumber(passportNumber) {}

// ************************************* Getters ************************************* //
int passengers::getId() const { return id; }
std::string passengers::getName() const { return name; }
std::string passengers::getPassportNumber() const { return passportNumber; }

// ************************************* Setters ************************************* //
void passengers::setName(const std::string& name) { this->name = name; }
void passengers::setPassportNumber(const std::string& passportNumber) { this->passportNumber = passportNumber; }


void passengers::updateInDB(sqlconnect& db) {
    std::stringstream query;
    query << "UPDATE passengers SET name='" << name
          << "', passportNumber='" << passportNumber
          << "' WHERE id=" << id;
    db.execute(query.str());
}


void passengers::deleteFromDB(sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM passengers WHERE id=" << id;
    db.execute(query.str());
}

// ************************************* static methods ************************************* // 
passengers passengers::getById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "SELECT name, passportNumber FROM passengers WHERE id=" << id;
    MYSQL_RES* res = db.execute(query.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            passengers p(id, row[0], row[1]);
            mysql_free_result(res);
            return p;
        }
        mysql_free_result(res);
    }
    return passengers(-1, "", "");
}

passengers passengers::getByPassportNumber(const std::string& passportNumber, sqlconnect& db) {
    std::stringstream query;
    query << "SELECT id, name FROM passengers WHERE passportNumber='" << passportNumber << "'";
    MYSQL_RES* res = db.execute(query.str());
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            passengers p(std::stoi(row[0]), row[1], passportNumber);
            mysql_free_result(res);
            return p;
        }
        mysql_free_result(res);
    }
    return passengers(-1, "", "");
}

std::vector<passengers> passengers::getAllPassengers(sqlconnect& db) {
    std::vector<passengers> all;
    std::string query = "SELECT id, name, passportNumber FROM passengers";
    MYSQL_RES* res = db.execute(query);
    if (res) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            all.emplace_back(std::stoi(row[0]), row[1], row[2]);
        }
        mysql_free_result(res);
    }
    return all;
}

void passengers::deleteById(int id, sqlconnect& db) {
    std::stringstream query;
    query << "DELETE FROM passengers WHERE id=" << id;
    db.execute(query.str());
}