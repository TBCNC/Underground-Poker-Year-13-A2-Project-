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
bool UserAccount::CreateAccount(sf::String password,sf::String email) {
	if (!UserExist()) {
		std::string tableName = "users";
		std::vector<std::vector<std::string>> results;
		std::vector<std::string> fields = { "Username","Password","Email" };
		std::vector<std::string> values = { this->username,PasswordHash::GeneratePassword(password),email };
		DBConnection db;
		db.ExecuteQuery_Insert(tableName, fields, values);
		db.ExecuteQuery_Insert_Blank("profile", "UID");
		db.ExecuteQuery_Insert_Blank("statistics", "UID");
		return true;
	}
	else
		return false;
}
bool UserAccount::UserExist()
{
	std::string tableName = "users";
	std::vector<std::vector<std::string>> results;
	std::vector<std::string> fields = { "COUNT(Password)" };
	std::vector<std::string> conditionFields, conditionArguments;
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
	return results.at(0).at(0) == "1";
}

void UserAccount::RetrieveInformation()
{

}
sf::Image GetProfilePicture() {

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
