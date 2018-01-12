//#include "Game.h"
#include "../Network/DBConnection.h"
#include <iostream>
//#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	/*
	DBConnection connection;
	std::vector<std::string> fields, arguments,defaultvec;
	fields.push_back("Username");
	fields.push_back("Password");
	arguments.push_back("fagoloid");
	arguments.push_back("Imaweeb");
	arguments.push_back("weebatgmail.com");
	connection.ExecuteQuery_Select("users", fields,defaultvec,defaultvec);
	system("pause");
	*/
	DBConnection connection;
	std::vector<std::string> fields, arguments, conditionFields, conditionArguments;
	fields.push_back("Password");
	arguments.push_back("newPassword");
	conditionFields.push_back("Email");
	conditionArguments.push_back("newEmail");
	connection.ExecuteQuery_Update("users",fields, arguments, conditionFields, conditionArguments);
}
 