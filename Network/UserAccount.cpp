#include "UserAccount.h"
//Until we find a solution for localtime_s

UserAccount::UserAccount() {

}
UserAccount::UserAccount(int UID, bool retrieveInfo) {
	this->UID = UID;
	if(retrieveInfo)
		RetrieveInformation();
	this->profilePicture = "resources/profilePic.png";
}
UserAccount::UserAccount(sf::String username) {
	this->username = username;
	RetrieveInformation();
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
	if (UserExist()) {
		DBConnection db;
		if (this->UID == 0)
			this->UID = stoi(db.ExecuteQuery_Select("users", { "UID" }, { "username" }, { (this->username) }).at(0).at(0));
		else
			this->username = db.ExecuteQuery_Select("users", { "username" }, { "UID" }, { std::to_string(this->UID) }).at(0).at(0);
		this->ELO = stoi(db.ExecuteQuery_Select("statistics", { "ELO_RANKING" }, { "UID" }, { std::to_string(this->UID) }).at(0).at(0));
		std::cout << "Username is:" << this->username.toAnsiString() << std::endl;
	}
}
std::string UserAccount::GetProfilePicture() {
	std::string tableName = "profile";
	std::vector<std::vector<std::string>> results;
	std::vector<std::string> fields = { "Profile_Pic" };
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
	std::string url = results.at(0).at(0);

	sf::Http http;
	sf::Http::Request req(url);
	sf::Http::Response response = http.sendRequest(req);
	std::string imageData = response.getBody();
	std::ofstream file;
	std::string newFileName;
	time_t t = time(0);
	struct tm * now = localtime(&t);
	newFileName = "resources/profilePictures/" + PasswordHash::GeneratePassword(std::to_string(now->tm_sec) + std::to_string(now->tm_min) + std::to_string(now->tm_hour) + std::to_string(now->tm_yday)) + ".png";//Random file name
	file.open(newFileName, std::ios::binary);
	file.write(imageData.c_str(),imageData.size());
	file.flush();
	file.close();
	return newFileName;
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
