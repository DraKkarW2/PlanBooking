#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <string>
#include "sqlconnect.h"

class passengers {
private:
    int id;
    std::string name;
    std::string passportNumber;

public:
    passengers(const std::string& name, const std::string& passportNumber, sqlconnect& db);

    int getId() const;
    void setId(int id);

    std::string getName() const;
    void setName(const std::string& name);

    std::string getPassportNumber() const;
    void setPassportNumber(const std::string& passportNumber);
};

#endif