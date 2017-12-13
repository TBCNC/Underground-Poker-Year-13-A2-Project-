#include "DBConnection.h"

DBConnection::DBConnection() {
	/*this->sql_driver = sql::mysql::get_mysql_driver_instance();
	this->sql_connection = this->sql_driver->connect("tcp://82.34.216.42:3306", DB_USERNAME, DB_PASSWORD);
	if (this->sql_connection->isValid())
		std::cout << "Connected!" << std::endl;
	else
		std::cout << "Uh oh!" << std::endl;*/
}
DBConnection::~DBConnection() {
	
}
void DBConnection::ExecuteQuery_Insert()
{
}
void DBConnection::ExecuteQuery_Select()
{
}
void DBConnection::ExecuteQuery_Update()
{
}
char* DBConnection::ClearString(char* query) {
	char* newString = nullptr;
	for (int c = 0; c < strlen(query); c++) {
		if (query[c] == '\'') {
			newString += '\'';
		}
		newString += query[c];
	}
	return newString;
}