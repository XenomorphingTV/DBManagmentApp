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
};

int getLevel(sql::Connection* con, std::string user);
std::string getUser(sql::Connection* cons);
bool getPass(sql::Connection* con, std::string user);