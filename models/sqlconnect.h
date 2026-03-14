#ifndef SQLCONNECT_H
#define SQLCONNECT_H

#include <mysql/mysql.h>
#include <string>

class sqlconnect {
private:
    std::string credentials;
    std::string password;
    MYSQL* conn;

public:
    sqlconnect(std::string credentials, std::string password);
    MYSQL_RES* execute(std::string query);
    ~sqlconnect();
};

#endif