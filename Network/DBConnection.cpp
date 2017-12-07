#include "DBConnection.h"

DBConnection::DBConnection() {
	try {
		this->dbConnection.Connect(DB_NAME, DB_USERNAME, DB_PASSWORD, SA_MySQL_Client);
		this->command.setConnection(&this->dbConnection);
	}
	catch (SAException &ex) {
		try {
			this->dbConnection.Rollback();
		}
		catch (SAException &ex2) {
		}
		printf("%s\n", (const char*)ex.ErrText());
		throw;
	}
}
DBConnection::~DBConnection() {
	this->dbConnection.Disconnect();
	this->dbConnection.Destroy();
}
void DBConnection::ExecuteQuery_Write(SAString query) {
	try {
		this->command.setCommandText(ClearString(query));
		this->command.Execute();
		this->dbConnection.Commit();
	}
	catch (SAException &ex) {
		try {
			this->dbConnection.Rollback();
		}
		catch (SAException &ex2) {

		}
		printf("%s\n", (const char*)ex.ErrText());
		throw;
	}
}
void DBConnection::ExecuteQuery_Read(SAString query, SAString fields[]) {
	try
	{
		this->command.setCommandText(ClearString(query));
		this->command.Execute();

	}catch(SAException &ex)
	{
		try
		{
			this->dbConnection.Rollback();
		}catch(SAException &ex2)
		{
			
		}
	}
}
SAString DBConnection::ClearString(SAString query) {
	SAString newString;
	for (int c = 0; c < query.GetLength(); c++) {
		if (query[c] == '\'') {
			newString += '\'';
		}
		newString += query[c];
	}
	return newString;
}