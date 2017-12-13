#include "DBConnection.h"

DBConnection::DBConnection() {
	
}
DBConnection::~DBConnection() {
	
}
void DBConnection::ExecuteQuery_Write() {
	
}
void DBConnection::ExecuteQuery_Read() {
	
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