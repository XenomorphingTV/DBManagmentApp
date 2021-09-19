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

// Getting users authentication level withou aany inputs after correct password and username input
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

// Comparing the user input to the database request
// Nothing is done to the result or input
std::string getUser(sql::Connection* con) {
	sql::Statement* stmt;
	sql::ResultSet* res;
	std::string user{};
	std::string returnUser{};
	con->setSchema("login");

	do{
		std::cout << "Username: ";
		std::cin >> user;
		clearScreen();
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT user FROM login.logins WHERE user=\"" + user + "\";");
		res->next();
		returnUser = res->getString("user");
		if (user != returnUser) std::cout << "Incorrect user\n";
	} while (user != returnUser);
	delete stmt;
	delete res;
	return user;
}


// After getting password input and de-hashing it to compare it
// We use a bcrypt library to hash and de-hash our passwords
bool getPass(sql::Connection* con, std::string user) {
	sql::Statement* stmt;
	sql::ResultSet* res;
	std::string pass{};
	std::string returnPassword{};
	con->setSchema("login");
	do{
		std::cout << "Password: ";
		std::cin >> pass;
		clearScreen();
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT password FROM logins WHERE user=\"" + user + "\";");
		res->next();
		returnPassword = res->getString("password");
		if (bcrypt::validatePassword(pass, returnPassword) != 1) std::cout << "Incorrect password\n";
	} while (bcrypt::validatePassword(pass, returnPassword) != 1); // Checking if de-hashed pass is equal to inputed password
	delete stmt;
	delete res;
	return 1;
}
