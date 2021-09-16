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

std::string getUser() {
	std::string user{};
	std::cout << "Username: ";
	std::cin >> user;
	clear_screen();
	return user;
}

std::string getPass() {
	std::string pass{};
	std::cout << "Password: ";
	std::cin >> pass;
	clear_screen();
	return pass;
}

void checkUserAndPass(sql::Driver* driver, sql::Connection* con) {
	sql::Statement* stmt;
	sql::ResultSet* res;
	std::string returnUser{};
	std::string returnPassword{};
	std::string user{ getUser() };
	std::string pass{ getPass() };
	con->setSchema("login");

	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM logins WHERE user=\"" + user + "\";");
	while (res->next()) {
		returnUser = res->getString("user");
		returnPassword = res->getString("password");
	}

	if ((returnUser == user) && (bcrypt::validatePassword(pass, returnPassword))) {
		std::cout << "Logged in\n";
	}
	else std::cout << "Failed\n";


}

void getConnection(std::string address, std::string user, std::string pass) {
	try {
		sql::Driver* driver;
		sql::Connection* con;

		driver = get_driver_instance();
		con = driver->connect(address, user, pass);
		checkUserAndPass(driver, con);
		}
	
	catch(sql::SQLException& e){
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << '\n';
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << '\n';
	}
}

