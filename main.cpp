#include <iostream>
#include <ctime>
#include "models/sqlconnect.h"
#include "models/plane.h"
#include "models/passengers.h"

using namespace std;

int main() {
    sqlconnect db("root", ""); 
    time_t now = time(nullptr);
    plane p("AF123", now, 180, db);

    cout << "Avion créé avec l'ID : " << p.getId() << endl;
    cout << "Numéro : " << p.getNumber() << ", capacité : " << p.getCapacity() << endl;

    passengers passengersA("Alice Dupont", "P1234567", db);
    std::cout << "ID: " << passengersA.getId() << std::endl;
    std::cout << "Name: " << passengersA.getName() << std::endl;
    std::cout << "Passport: " << passengersA.getPassportNumber() << std::endl;
    return 0;
}