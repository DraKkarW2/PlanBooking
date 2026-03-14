#include "plane.h"
#include <iostream>
using namespace std;

plane::plane(string number, time_t departure_time, int capacity, sqlconnect& db) {
    string selectQuery = "SELECT id FROM plane WHERE number='" + number
                         + "' AND departure_time=" + to_string(departure_time) + " LIMIT 1";
    MYSQL_RES* res = db.execute(selectQuery);
    if (res && mysql_num_rows(res) > 0) {
        MYSQL_ROW row = mysql_fetch_row(res);
        this->id = row ? stoi(row[0]) : -1;
        mysql_free_result(res);
        cout << "plane already exists with id " << this->id << endl;
    } else {
        string insertQuery = "INSERT INTO plane(number, capacity, departure_time) VALUES ('"
                             + number + "'," + to_string(capacity) + "," + to_string(departure_time) + ")";
        db.execute(insertQuery);

        res = db.execute("SELECT LAST_INSERT_ID()");
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            this->id = row ? stoi(row[0]) : -1;
            mysql_free_result(res);
        } else {
            this->id = -1;
        }
        cout << "plane created with id " << this->id << endl;
    }

    this->number = number;
    this->capacity = capacity;
    this->departure_time = departure_time;
}

int plane::getId() { return id; }
string plane::getNumber() { return number; }
int plane::getCapacity() { return capacity; }