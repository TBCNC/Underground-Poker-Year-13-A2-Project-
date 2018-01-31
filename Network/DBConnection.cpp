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
	//delete this->sql_connection;
	//delete this->sql_driver;
	this->sql_connection->close();
}
///<summary>
///Insert a new row into a MYSQL table
///</summary>
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
///<summary>
///Select information from columns of a MYSQL table based on conditions
///</summary>
std::vector<std::vector<std::string>> DBConnection::ExecuteQuery_Select(std::string table, std::vector<std::string> fields, std::vector<std::string> conditionFields=std::vector<std::string>(), std::vector<std::string> conditionArguments=std::vector<std::string>())
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
		std::vector<std::vector<std::string>> return_results;
		while (results->next()) {
			std::vector<std::string> babyResults;
			for (int c = 0; c < fields.size(); c++) {
				babyResults.push_back(results->getString(fields.at(c)));
			}
			return_results.push_back(babyResults);
		}
		delete prepared_statement;
		return return_results;
	}
	catch (sql::SQLException e) {
		std::cout << "Caught exception" << std::endl;
		std::cout << e.getSQLState() << std::endl;
		std::cout << e.getErrorCode() << std::endl;
	}
}
///<summary>
///Update information that is currently in a MYSQL table
///</summary>
void DBConnection::ExecuteQuery_Update(std::string table, std::vector<std::string> fields, std::vector<std::string> arguments, std::vector<std::string> conditionFields = std::vector<std::string>(), std::vector<std::string> conditionArguments = std::vector<std::string>())
{
	std::string sqlQuery = "UPDATE " + (std::string)(DB_DATABASE)+"."+table + " SET ";
	for (int c = 0; c < fields.size(); c++) {
		sqlQuery += fields.at(c) + "=?";
		if (c != (fields.size() - 1))
			sqlQuery += ",";
	}
	if (conditionFields.size() > 0) {
		sqlQuery += " WHERE ";
		for (int i = 0; i < conditionFields.size(); i++) {
			sqlQuery += (conditionFields.at(i) + "=?");
		}
	}
	sqlQuery += ";";
	std::cout << "Preparing query " << sqlQuery << std::endl;
	try {
		sql::PreparedStatement *prepared_statement = NULL;
		prepared_statement = this->sql_connection->prepareStatement(sqlQuery);
		for (int c = 0; c < arguments.size(); c++) {
			if (arguments.at(c).find_first_not_of("0123456789") == std::string::npos) {
				prepared_statement->setInt(c + 1, stoi(arguments.at(c)));
			}
			else {
				prepared_statement->setString(c + 1, arguments.at(c));
			}
		}
		for (int i = 0; i < conditionArguments.size(); i++) {
			if (conditionArguments.at(i).find_first_not_of("0123456789") == std::string::npos) {
				prepared_statement->setInt(i + 1+arguments.size(), stoi(conditionArguments.at(i)));
			}
			else {
				prepared_statement->setString(i + 1+arguments.size(), conditionArguments.at(i));
			}
		}
		std::cout << "Executing..." << std::endl;
		prepared_statement->execute();
		delete prepared_statement;
	}
	catch (sql::SQLException e) {
		std::cout << "Caught exception" << std::endl;
		std::cout << "SQL state:" << e.getSQLState() << std::endl;
		std::cout << "SQL EC:" << e.getErrorCode() << std::endl;
	}
}
void DBConnection::ExecuteQuery_Delete(std::string tableName, std::vector<std::string> conditionFields, std::vector<std::string> conditionArguments)
{
	std::string sqlQuery = "DELETE FROM underground_poker." + tableName;
	if (conditionFields.size() > 0) {
		sqlQuery += " WHERE ";
		for (int i = 0; i < conditionFields.size(); i++) {
			sqlQuery += (conditionFields.at(i) + "=?");
			if(i!=conditionFields.size()-1)
				sqlQuery += " AND ";
		}
	}
	sqlQuery += ";";
	std::cout << "Preparing query..." << std::endl;
	std::cout << "Query:" << sqlQuery;
	try {
		sql::PreparedStatement *prepared_statement = NULL;
		prepared_statement = this->sql_connection->prepareStatement(sqlQuery);
		for (int i = 0; i < conditionArguments.size(); i++) {
			if (conditionArguments.at(i).find_first_not_of("0123456789") == std::string::npos) {
				prepared_statement->setInt(i, stoi(conditionArguments.at(i)));
			}
			else {
				prepared_statement->setString(i+1, conditionArguments.at(i));
			}
		}
		std::cout << "Executing..." << std::endl;
		prepared_statement->execute();
		delete prepared_statement;
	}
	catch (sql::SQLException e) {
		std::cout << "Caught exception" << std::endl;
		std::cout << "SQL state:" << e.getSQLState() << std::endl;
		std::cout << "SQL EC:" << e.getErrorCode() << std::endl;
	}
}
void DBConnection::ExecuteQuery_Insert_Blank(std::string tableName,std::string autoIncrementName)
{
	std::string sqlQuery = "INSERT INTO " + (std::string)DB_DATABASE + "." + tableName + " (" + autoIncrementName + ") VALUES(null);";
	try {
		sql::PreparedStatement *prepared_statement = NULL;
		prepared_statement = this->sql_connection->prepareStatement(sqlQuery);
		prepared_statement->execute();
		delete prepared_statement;
	}
	catch (sql::SQLException e) {
		std::cout << "Caught exception" << std::endl;
		std::cout << "SQL state:" << e.getSQLState() << std::endl;
		std::cout << "SQL EC:" << e.getErrorCode() << std::endl;
	}
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