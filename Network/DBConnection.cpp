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
void DBConnection::ExecuteQuery_Insert(std::string tableName,std::vector<std::string> fields, std::vector<std::string> arguments)//Complete
{
	//Constructing a string for the query. Also, for arguments check whether they can be converted to integer.
	//Also going to be using prepared statements.
	std::string sqlQuery = "INSERT INTO " + (std::string)DB_DATABASE + "." + tableName + " (";
	for (int c = 0; c < fields.size(); c++) {
		sqlQuery += fields.at(c);
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
	std::cout << "Prepared query:" << sqlQuery << std::endl;
	try {
		sql::PreparedStatement *prepared_statement = NULL;
		prepared_statement = this->sql_connection->prepareStatement(sqlQuery);
		for (int i = 0; i < arguments.size(); i++) {
			if (arguments.at(i).find_first_not_of("0123456789") == std::string::npos) {
				prepared_statement->setInt(i+1, stoi(arguments.at(i)));
			}
			else {
				prepared_statement->setString(i+1, arguments.at(i));
			}
		}
		std::cout << "Executing query..." << std::endl;
		prepared_statement->execute();
		delete prepared_statement;
	}
	catch (sql::SQLException e) {
		std::cout << "Caught exception" << std::endl;
		std::cout << e.getSQLState() << std::endl;
		std::cout << e.getErrorCode() << std::endl;
	}
} 
void DBConnection::ExecuteQuery_Select(std::string table, std::vector<std::string> fields, std::vector<std::string> conditionFields=std::vector<std::string>(), std::vector<std::string> conditionArguments=std::vector<std::string>())
{
	std::string sqlQuery = "SELECT ";
	for (int c = 0; c < fields.size(); c++) {
		sqlQuery += fields.at(c);
		if (c != fields.size() - 1)
			sqlQuery += ",";
	}
	sqlQuery += (" FROM " + ((std::string)DB_DATABASE+'.'+table));
	if (conditionFields.size() > 0) {
		sqlQuery += " WHERE ";
		for (int c = 0; c < conditionFields.size(); c++) {
			sqlQuery += (conditionFields.at(c) + "=?");
			if (c != conditionFields.size() - 1) {
				sqlQuery += " AND ";
			}
		}
	}
	sqlQuery += ";";
	std::cout << "Prepared query:" << sqlQuery << std::endl;
	try {
		sql::PreparedStatement *prepared_statement = NULL;
		prepared_statement = this->sql_connection->prepareStatement(sqlQuery);
		for (int c = 0; c < conditionArguments.size(); c++) {
			if (conditionArguments.at(c).find_first_not_of("0123456789") == std::string::npos) {
				prepared_statement->setInt(c + 1, stoi(conditionArguments.at(c)));
			}
			else {
				prepared_statement->setString(c + 1, conditionArguments.at(c));
			}
		}
		std::cout << "Executing query..." << std::endl;
		sql::ResultSet *results = prepared_statement->executeQuery();
		while (results->next()) {
			std::cout << "Username:" << results->getString("Username") << "	Password:" << results->getString("Password") << std::endl;
		}
	}
	catch (sql::SQLException e) {
		std::cout << "Caught exception" << std::endl;
		std::cout << e.getSQLState() << std::endl;
		std::cout << e.getErrorCode() << std::endl;
	}
}
void DBConnection::ExecuteQuery_Update()
{
}
char* DBConnection::ClearString(char* query) {//May not need this now since we are using prepared statements
	char* newString = nullptr;
	for (int c = 0; c < strlen(query); c++) {
		if (query[c] == '\'') {
			newString += '\'';
		}
		newString += query[c];
	}
	return newString;
}