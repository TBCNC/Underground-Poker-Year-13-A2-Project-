//#include "Game.h"
#include "../Network/DBConnection.h"
#include <Windows.h>

int main() {
	DBConnection database_connection;
	std::vector<std::string> testVector1;
	testVector1.push_back("id");
	testVector1.push_back("name");
	std::vector<std::string> testVector2;
	testVector2.push_back("1234");
	testVector2.push_back("weeabooJones");
	database_connection.ExecuteQuery_Insert("table", testVector1, testVector2);
	system("pause");
}
 