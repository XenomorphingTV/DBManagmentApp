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
	// Connect to MySQL
	getConnection(sqlAddress, sqlUser, sqlPass, loggedIn.driver, loggedIn.con, loggedIn.stmt, loggedIn.res);
	// Login
	loggedIn.user = getUser(loggedIn.con, loggedIn.stmt, loggedIn.res);
	loggedIn.passAuthenticated = getPass(loggedIn.con, loggedIn.stmt, loggedIn.res);
	loggedIn.level = getLevel(loggedIn.con, loggedIn.stmt, loggedIn.res, loggedIn.user);
	// Main menu


	return 0;
}
