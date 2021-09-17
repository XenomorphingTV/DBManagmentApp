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

std::string getLevel(sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res, std::string user) {
	int level{};
	con->setSchema("login");
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT level FROM logins WHERE user=\"" + user + "\";");
	level = res->getInt("level");
	return user;
}

std::string getUser(sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res) {
	std::string user{};
	std::string returnUser{};
	con->setSchema("login");
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT user FROM logins WHERE user=\"" + user + "\";");
	returnUser = res->getString("user");

	while (user != returnUser) {
		std::cout << "Username: ";
		std::cin >> user;
		clear_screen();
		if (user != returnUser) std::cout << "Incorrect user";
	}
	return user;
}

bool getPass(sql::Connection* con, sql::Statement* stmt, sql::ResultSet* res) {
	std::string pass{};
	std::string returnPassword{};
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT password FROM logins WHERE password=\"" + pass + "\";");
	returnPassword = res->getString("password");
	while (bcrypt::validatePassword(pass, returnPassword) != 1) {
		std::cout << "Password: ";
		std::cin >> pass;
		clear_screen();
		if (bcrypt::validatePassword(pass, returnPassword) != 1) std::cout << "Incorrect password";
	}
	return 1;
}

void getConnection(std::string address, std::string user, std::string pass) {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		driver = get_driver_instance();
		con = driver->connect(address, user, pass);
	}
	catch(sql::SQLException& e){
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << '\n';
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << '\n';
	}
}

