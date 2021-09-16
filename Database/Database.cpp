#include <iostream>
#include <string>
#include "Authentication.h"

int main()
{
	// Define login to MySQL
	const std::string sqlAddress = "localhost";
	const std::string sqlUser = "root";
	const std::string sqlPass = "stefan";

	// Get login and pass
	getConnection(sqlAddress, sqlUser, sqlPass);
	// Connect to MySQL
	// Get login
	// Get password
	// Main menu


	return 0;
}
