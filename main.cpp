#include <iostream>
#include <limits>
#include <ctime>
#include "models/sqlconnect.h"
#include "models/plane.h"
#include "models/flight.h"
#include "models/passengers.h"
#include "models/booking.h"

using namespace std;

void printHeader() {
    cout << "==============================\n";
    cout << "   AIRLINE MANAGEMENT SYSTEM  \n";
    cout << "==============================\n";
}

void printMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Ajouter un avion\n";
    cout << "2. Ajouter un vol\n";
    cout << "3. Ajouter un passager\n";
    cout << "4. Créer une réservation\n";
    cout << "5. Lister avions\n";
    cout << "6. Lister vols\n";
    cout << "7. Lister passagers\n";
    cout << "8. Lister réservations\n";
    cout << "9. Supprimer un avion\n";
    cout << "10. Supprimer un vol\n";
    cout << "11. Supprimer un passager\n";
    cout << "12. Supprimer une réservation\n";
    cout << "0. Quitter\n";
    cout << "Choix : ";
}

int main() {
    sqlconnect db("root", ""); 
    int choice;

    do {
        printHeader();
        printMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: { 
                string number;
                int capacity;
                cout << "Numéro avion : "; getline(cin, number);
                cout << "Capacité : "; cin >> capacity; cin.ignore();
                plane p(number, time(nullptr), capacity, db);
                cout << "Avion créé : ID=" << p.getId() << "\n";
                break;
            }
            case 2: { 
                string flightNum; int capacity, planeId;
                cout << "Numéro vol : "; getline(cin, flightNum);
                cout << "Capacité vol : "; cin >> capacity; cin.ignore();
                cout << "ID avion associé : "; cin >> planeId; cin.ignore();
                try {
                    flight f(flightNum, capacity, planeId, db);
                    cout << "Vol créé : ID=" << f.getId() << "\n";
                } catch (const exception& e) {
                    cout << e.what() << "\n";
                }
                break;
            }
            case 3: { 
                string name, passport;
                cout << "Nom passager : "; getline(cin, name);
                cout << "Passport : "; getline(cin, passport);
                passengers p(name, passport, db);
                cout << "Passager créé : ID=" << p.getId() << "\n";
                break;
            }
            case 4: { 
                int flightId, passengerId; double price;
                cout << "Flight ID : "; cin >> flightId; cin.ignore();
                cout << "Passenger ID : "; cin >> passengerId; cin.ignore();
                cout << "Price : "; cin >> price; cin.ignore();
                try {
                    booking b(price, time(nullptr), flightId, passengerId, db);
                    cout << "Booking créé : ID=" << b.getId() << "\n";
                } catch (const exception& e) {
                    cout << e.what() << "\n";
                }
                break;
            }
            case 5: {
                auto planes = plane::getAllPlanes(db);
                for (auto& p : planes)
                    cout << "ID=" << p.getId() << ", Num=" << p.getNumber() << ", Cap=" << p.getCapacity() << "\n";
                break;
            }
            case 6: {
                auto flights = flight::getAllFlights(db);
                for (auto& f : flights)
                    cout << "ID=" << f.getId() << ", Num=" << f.getFlightNumber() 
                         << ", Cap=" << f.getCapacity() << ", Plane ID=" << f.getPlaneId() << "\n";
                break;
            }
            case 7: {
                auto ps = passengers::getAllPassengers(db);
                for (auto& p : ps)
                    cout << "ID=" << p.getId() << ", Name=" << p.getName() 
                         << ", Passport=" << p.getPassportNumber() << "\n";
                break;
            }
            case 8: {
                auto bs = booking::getAllBookings(db);
                for (auto& b : bs)
                    cout << "ID=" << b.getId() << ", Flight ID=" << b.getFlightId() 
                         << ", Passenger ID=" << b.getPassengerId() << ", Price=" << b.getPrice() << "\n";
                break;
            }
            case 9: {
                int id; cout << "ID avion à supprimer : "; cin >> id; cin.ignore();
                plane::deleteById(id, db);
                cout << "Avion supprimé si existant.\n";
                break;
            }
            case 10: {
                int id; cout << "ID vol à supprimer : "; cin >> id; cin.ignore();
                flight::deleteById(id, db);
                cout << "Vol supprimé si existant.\n";
                break;
            }
            case 11: {
                int id; cout << "ID passager à supprimer : "; cin >> id; cin.ignore();
                passengers::deleteById(id, db);
                cout << "Passager supprimé si existant.\n";
                break;
            }
            case 12: {
                int id; cout << "ID booking à supprimer : "; cin >> id; cin.ignore();
                booking::deleteById(id, db);
                cout << "Booking supprimé si existant.\n";
                break;
            }
            case 0: 
                cout << "Au revoir !\n";
                break;
            default:
                cout << "Choix invalide.\n";
        }

    } while(choice != 0);

    return 0;
}