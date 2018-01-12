//#include "Game.h"
#include "../Network/DBConnection.h"
#include <iostream>
//#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	DBConnection connection;
	std::vector<std::string> fields, arguments,defaultvec;
	fields.push_back("Username");
	fields.push_back("Password");
	arguments.push_back("fagoloid");
	arguments.push_back("Imaweeb");
	arguments.push_back("weebatgmail.com");
	connection.ExecuteQuery_Select("users", fields,defaultvec,defaultvec);
	system("pause");
}
 