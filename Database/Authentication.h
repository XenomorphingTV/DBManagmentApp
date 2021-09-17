#pragma once
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <iostream>
#include <string>

struct loggedUser {
	std::string user{};
	bool passAuthenticated{};
	int level{};
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
};

int getLevel(sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res, std::string user);
std::string getUser(sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res);
bool getPass(sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res);
void getConnection(std::string address, std::string user, std::string pass, sql::Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res);