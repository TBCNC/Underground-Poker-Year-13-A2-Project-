#include "../SQL/include/SQLAPI.h"
#include <iostream>
#include <stdio.h> //I am actually a R E T A R D
#include <string>
#define DB_USERNAME "root"
#define DB_PASSWORD "test123"
#define DB_NAME "82.39.29.160@underground_poker"
#pragma once

class DBConnection {
public:
	DBConnection();
	~DBConnection();
	void ExecuteQuery_Write(SAString query);
	void ExecuteQuery_Read(SAString query, SAString fields[]);
private:
	SAConnection dbConnection;
	SACommand command;
	SAString ClearString(SAString query);
};