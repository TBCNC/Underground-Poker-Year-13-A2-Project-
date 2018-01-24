#include "UserAccount.h"

UserAccount::UserAccount() {

}
UserAccount::UserAccount(int UID) {
	this->UID = UID;
}
UserAccount::UserAccount(sf::String username) {
	this->username = username;
}
bool UserAccount::Login(sf::String password)
{
	return PasswordHash::ComparePasswords(password, GetPasswordHash());
}
void UserAccount::CreateAccount() {

}

bool UserAccount::UserExist()
{
	return false;
}

void UserAccount::RetrieveInformation()
{
}
sf::String UserAccount::GetPasswordHash()
{
	std::string tableName = "users";
	std::vector<std::vector<std::string>> results;
	std::vector<std::string> fields = { "Password" };
	std::vector<std::string> conditionFields,conditionArguments;
	if (this->UID == 0) {
		conditionFields = { "Username" };
		conditionArguments = { this->username };
	}
	else {
		conditionFields = { "UID" };
		conditionArguments = { std::to_string(this->UID) };
	}
	DBConnection db;
	results = db.ExecuteQuery_Select(tableName, fields, conditionFields, conditionArguments);
	return results.at(0).at(0);
}
