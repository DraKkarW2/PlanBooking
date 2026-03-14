#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <string>
#include <vector>
#include "sqlconnect.h"

class passengers {
private:
    int id;
    std::string name;
    std::string passportNumber;

public:
    // constructor avec insert bdd
    passengers(const std::string& name, const std::string& passportNumber, sqlconnect& db);
    // constructor sans insert bdd
    passengers(int id, const std::string& name, const std::string& passportNumber);

    // ************************************* Getters ************************************* //
    int getId() const;
    std::string getName() const;
    std::string getPassportNumber() const;

    // ************************************* Setters ************************************* //
    void setName(const std::string& name);
    void setPassportNumber(const std::string& passportNumber);

    void updateInDB(sqlconnect& db);
    void deleteFromDB(sqlconnect& db);
    
    // ************************************* static methods ************************************* // 
    static passengers getById(int id, sqlconnect& db);
    static passengers getByPassportNumber(const std::string& passportNumber, sqlconnect& db);
    static std::vector<passengers> getAllPassengers(sqlconnect& db);
    static void deleteById(int id, sqlconnect& db);
};

#endif