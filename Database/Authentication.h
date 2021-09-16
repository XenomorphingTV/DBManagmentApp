#pragma once
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <iostream>
#include <string>

void checkUserAndPass(sql::Driver* driver, sql::Connection* con);
void getConnection(std::string address, std::string user, std::string pass);