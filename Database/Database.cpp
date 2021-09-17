#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Authentication.h"

int main()
{
	// Define login to MySQL
	const std::string sqlAddress = "localhost";
	const std::string sqlUser = "root";
	const std::string sqlPass = "stefan";
	loggedUser loggedIn{};

	//Initialise MySQL class
	// Connect to MySQL
	do {
		try {
			sql::Driver* driver;
			sql::Connection* con;
			driver = get_driver_instance();
			con = driver->connect(sqlAddress, sqlUser, sqlPass);
			loggedIn.user = getUser(con);
			loggedIn.passAuthenticated = getPass(con, loggedIn.user);
			loggedIn.level = getLevel(con, loggedIn.user);
		}

		// Catch any errors thrown by MySQL
		catch (sql::SQLException& e) {
			if (e.getErrorCode() == 0) {
				std::cout << "Incorrect Username/Password\n";
			}
			else {
				std::cout << "# ERR: SQLException in " << __FILE__;
				std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << '\n';
				std::cout << "# ERR: " << e.what();
				std::cout << " (MySQL error code: " << e.getErrorCode();
				std::cout << ", SQLState: " << e.getSQLState() << " )" << '\n';
			}
		}
	} while (loggedIn.passAuthenticated != 1);

	// Login
	// Main menu


	return 0;
}
