#include <iostream>
#include <stdio.h>
#include <string>
#include <mysql_connection.h>
#define DB_USERNAME "root"
#define DB_PASSWORD "test123"
#define DB_NAME "82.34.216.42@underground_poker"
#pragma once

class DBConnection {
public:
	DBConnection();
	~DBConnection();
	void ExecuteQuery_Write();
	void ExecuteQuery_Read();
private:
	char* ClearString(char* query);
};