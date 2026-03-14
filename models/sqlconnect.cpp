#include "sqlconnect.h"
#include <iostream>
using namespace std;

sqlconnect::sqlconnect(string credentials, string password) {
    this->credentials = credentials;
    this->password = password;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", credentials.c_str(), password.c_str(),
                            "flightbdd", 3306, NULL, 0)) {
        cout << "Erreur connexion : " << mysql_error(conn) << endl;
    } else {
        cout << "Connexion réussie" << endl;
    }
}

MYSQL_RES* sqlconnect::execute(string query) {
    if (mysql_query(conn, query.c_str())) {
        cout << "Erreur query : " << mysql_error(conn) << endl;
        return nullptr;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    return res;
}

sqlconnect::~sqlconnect() {
    mysql_close(conn);
}