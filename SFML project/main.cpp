#include "../Network/DBConnection.h"
//#include "Game.h"
#include "../Network/PasswordHash.h"
#include "../Network/Cards.h"
#include <iostream>
//#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	srand(std::time(0));
	std::string password1, password2;
	std::cout << "Enter a password:";
	std::cin >> password1;
	password1 = PasswordHash::GeneratePassword(password1);
	std::cout << password1 << std::endl;
	std::cout << "Enter a password to see if it matches:";
	std::cin >> password2;
	if (PasswordHash::ComparePasswords(password2, password1))
		std::cout << "They match!" << std::endl;
	else
		std::cout << "They don't match!" << std::endl;
	system("pause");
}
 