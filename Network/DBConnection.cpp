#include "DBConnection.h"

DBConnection::DBConnection() {
	std::cout << "Connecting..." << std::endl;
	this->sql_driver = sql::mysql::get_mysql_driver_instance();
	this->sql_connection = this->sql_driver->connect("tcp://82.34.216.42:3306", DB_USERNAME, DB_PASSWORD);
	if (this->sql_connection->isValid())
		std::cout << "Connected!" << std::endl;
	else
		std::cout << "Uh oh!" << std::endl;
}
DBConnection::~DBConnection() {
	delete this->sql_connection;
	delete this->sql_driver;
}
void DBConnection::ExecuteQuery_Insert(std::string tableName,std::vector<std::string> fields, std::vector<std::string> arguments)
{
	//Constructing a string for the query. Also, for arguments check whether they can be converted to integer.
	//Also going to be using prepared statements.
	std::string sqlQuery = "INSERT INTO ? (";
	for (int c = 0; c < fields.size(); c++) {
		sqlQuery += "?";
		if (c != fields.size() - 1)
			sqlQuery += ",";
		else
			sqlQuery += ")";
	}
	sqlQuery += " VALUES(";
	for (int c = 0; c < arguments.size(); c++) {
		sqlQuery += "?";
		if (c != fields.size() - 1)
			sqlQuery += ",";
		else
			sqlQuery += ");";
	}
	std::cout << sqlQuery << std::endl;
	sql::PreparedStatement *prepared_statement = NULL;
	prepared_statement = this->sql_connection->prepareStatement(sqlQuery);
	prepared_statement->setString(1, tableName);
	for (int c = 0; c < fields.size(); c++) {
		prepared_statement->setString(c + 2, fields.at(c));
	}
	for (int i = 0; i < arguments.size(); i++) {
		if (arguments.at(i).find_first_not_of("0123456789") == std::string::npos) {
			prepared_statement->setInt(fields.size() + 2 + i, stoi(arguments.at(i)));
		}
		else {
			prepared_statement->setString(fields.size() + 2 + i, arguments.at(i));
		}
	}
	prepared_statement->execute();
	delete prepared_statement;
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