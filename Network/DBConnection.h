#include <iostream>
#include <stdio.h>
#include <string>
#include <mysql_connection.h>
#include <mysql_driver.h>
#define DB_USERNAME "root"
#define DB_PASSWORD "testPassword27"
#define DB_IP "82.34.216.42"
#define DB_DATABASE "underground_poker"
#pragma once

class DBConnection {
public:
	DBConnection();
	~DBConnection();
	void ExecuteQuery_Insert();
	void ExecuteQuery_Select();
	void ExecuteQuery_Update();
private:
	char* ClearString(char* query);
	sql::mysql::MySQL_Driver *sql_driver;
	sql::Connection *sql_connection;
};