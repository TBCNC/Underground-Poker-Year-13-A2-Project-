//#include "Game.h"
#include "../Network/DBConnection.h"
#include <Windows.h>

int main() {
	DBConnection database_connection;
	std::vector<std::string> testVector1;
	testVector1.push_back("Username");
	testVector1.push_back("Password");
	testVector1.push_back("Email");
	std::vector<std::string> testVector2;
	testVector2.push_back("newUser");
	testVector2.push_back("weeabooJones");
	testVector2.push_back("newEmail");
	database_connection.ExecuteQuery_Insert("users", testVector1, testVector2);
	system("pause");
}
 