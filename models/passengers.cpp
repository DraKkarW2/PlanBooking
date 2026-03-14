#include "passengers.h"
#include <iostream>
#include "sqlconnect.h"

passengers::passengers(const std::string& name, const std::string& passportNumber, sqlconnect& db) {
    std::string selectQuery = "SELECT id FROM passengers WHERE name='" + name
                              + "' AND passportNumber='" + passportNumber + "' LIMIT 1";
    MYSQL_RES* res = db.execute(selectQuery);
    if (res && mysql_num_rows(res) > 0) {
        MYSQL_ROW row = mysql_fetch_row(res);
        this->id = row ? std::stoi(row[0]) : -1;
        mysql_free_result(res);
        std::cout << "passenger already exists with id " << this->id << std::endl;
    } else {
        std::string insertQuery = "INSERT INTO passengers(name, passportNumber) VALUES ('"
                                  + name + "', '" + passportNumber + "')";
        db.execute(insertQuery);
        res = db.execute("SELECT LAST_INSERT_ID()");
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            this->id = row ? std::stoi(row[0]) : -1;
            mysql_free_result(res);
        } else {
            this->id = -1;
        }
        std::cout << "passenger created with id " << this->id << std::endl;
    }

    this->name = name;
    this->passportNumber = passportNumber;
}

int passengers::getId() const {
    return this->id;
}

void passengers::setId(int id) {
    this->id = id;
}

std::string passengers::getName() const {
    return this->name;
}

void passengers::setName(const std::string& name) {
    this->name = name;
}

std::string passengers::getPassportNumber() const {
    return this->passportNumber;
}

void passengers::setPassportNumber(const std::string& passportNumber) {
    this->passportNumber = passportNumber;
}