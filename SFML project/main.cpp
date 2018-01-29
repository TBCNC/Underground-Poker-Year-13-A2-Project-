#include "../Network/DBConnection.h"
#include "Game.h"
#include "../Network/PasswordHash.h"
#include "../Network/Cards.h"
#include "../Network/Server.h"
#include "../Network/UserAccount.h"
#include <iostream>
#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	//Server server(666);
	//server.Start();

	Game game(1600, 900);
	game.Run();
}
/*
//UserAccount account(1);
//account.GetPasswordHash();
//system("pause");
//DBConnection db;
//std::vector<std::vector<std::string>> results =db.ExecuteQuery_Select("users", { "Password" }, {"UID"}, {"1"});
//system("pause");
//std::cout << PasswordHash::GeneratePassword("testPassword");
std::string username;
std::string password;
std::cout << "Username:";
std::cin >> username;
std::cout << "Password:";
std::cin >> password;
std::cout << "Checking credentials..." << std::endl;
UserAccount account(username);
if (account.Login(password)) {
std::cout << "Logged in!" << std::endl;
}
else {
std::cout << "Failed to log in." << std::endl;
}
system("pause");
*/