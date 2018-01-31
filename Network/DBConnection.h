#include <iostream>
#include <stdio.h>
#include <string>
#include <mysql_connection.h>
#include <cppconn\prepared_statement.h>
#include <mysql_driver.h>
#include <vector>
#define DB_USERNAME "root"//Not going to use root in the future.
#define DB_PASSWORD "generalPassword2*"
#define DB_DATABASE "underground_poker"
#pragma once

class DBConnection {
public:
	DBConnection();
	~DBConnection();
	void ExecuteQuery_Insert(std::string tableName,std::vector<std::string> fields, std::vector<std::string> arguments);
	std::vector<std::vector<std::string>> ExecuteQuery_Select(std::string table, std::vector<std::string> fields,std::vector<std::string> conditionFields, std::vector<std::string> conditionArguments);
	void ExecuteQuery_Update(std::string table, std::vector<std::string> fields,std::vector<std::string> arguments,std::vector<std::string> conditionFields, std::vector<std::string> conditionArguments);
	void ExecuteQuery_Insert_Blank(std::string tableName,std::string autoIncrementName);
	void ExecuteQuery_Delete(std::string tableName, std::vector<std::string> conditionFields, std::vector<std::string> conditionArguments);
private:
	char* ClearString(char* query);
	sql::mysql::MySQL_Driver *sql_driver;
	sql::Connection *sql_connection;
};