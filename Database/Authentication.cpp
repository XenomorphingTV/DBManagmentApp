#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "bcrypt.h"
#include "Clear.h"

int getLevel(sql::Connection* con, std::string user) {
	sql::Statement* stmt;
	sql::ResultSet* res;
	int level{};
	con->setSchema("login");
	stmt = con->createStatement();	
	res = stmt->executeQuery("SELECT level FROM logins WHERE user=\"" + user + "\";");
	res->next();
	level = res->getInt("level");
	delete stmt;
	delete res;
	return level;
}

std::string getUser(sql::Connection* con) {
	sql::Statement* stmt;
	sql::ResultSet* res;
	std::string user{};
	std::string returnUser{};
	con->setSchema("login");

	do{
		std::cout << "Username: ";
		std::cin >> user;
		clear_screen();
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT user FROM login.logins WHERE user=\"" + user + "\";");
		res->next();
		returnUser = res->getString("user");
		if (user != returnUser) std::cout << "Incorrect user";
	} while (user != returnUser);
	delete stmt;
	delete res;
	return user;
}

bool getPass(sql::Connection* con, std::string user) {
	sql::Statement* stmt;
	sql::ResultSet* res;
	std::string pass{};
	std::string returnPassword{};
	con->setSchema("login");
	do{
		std::cout << "Password: ";
		std::cin >> pass;
		clear_screen();
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT password FROM logins WHERE user=\"" + user + "\";");
		res->next();
		returnPassword = res->getString("password");
		if (bcrypt::validatePassword(pass, returnPassword) != 1) std::cout << "Incorrect password";
	} while (bcrypt::validatePassword(pass, returnPassword) != 1);
	delete stmt;
	delete res;
	return 1;
}
