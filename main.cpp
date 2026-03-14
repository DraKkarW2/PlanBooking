#include <iostream>
#include <ctime>
#include "models/sqlconnect.h"
#include "models/plane.h"
#include "models/passengers.h"
#include "models/flight.h"
#include "models/booking.h"

using namespace std;

int main() {
    sqlconnect db("root", "");  

    time_t now = time(nullptr);


    plane p("AF123", now, 180, db);
    cout << "Avion créé : ID=" << p.getId() << ", Numéro=" << p.getNumber()
         << ", Capacité=" << p.getCapacity() << endl;


    flight f("AF123-01", 150, p.getId(), db);
    cout << "Vol créé : ID=" << f.getId() << ", Numéro=" << f.getFlightNumber()
         << ", Capacité=" << f.getCapacity() << ", Plane ID=" << f.getPlaneId() << endl;


    passengers passengerA("Alice Dupont", "P1234567", db);
    passengers passengerB("Bob Martin", "P7654321", db);

    cout << "Passager A : ID=" << passengerA.getId() << ", Nom=" << passengerA.getName()
         << ", Passport=" << passengerA.getPassportNumber() << endl;

    cout << "Passager B : ID=" << passengerB.getId() << ", Nom=" << passengerB.getName()
         << ", Passport=" << passengerB.getPassportNumber() << endl;


    booking booking1(199.99, now, f.getId(), passengerA.getId(), db);
    booking booking2(249.99, now, f.getId(), passengerB.getId(), db);

    cout << "Booking1 : ID=" << booking1.getId() << ", Flight ID=" << booking1.getFlightId()
         << ", Passenger ID=" << booking1.getPassengerId() << ", Price=" << booking1.getPrice() << endl;

    cout << "Booking2 : ID=" << booking2.getId() << ", Flight ID=" << booking2.getFlightId()
         << ", Passenger ID=" << booking2.getPassengerId() << ", Price=" << booking2.getPrice() << endl;

    return 0;
}