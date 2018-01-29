//#include "../Network/UserAccount.h"
#include "Game.h"
#include <iostream>
#include "../Network/UserAccount.h"

int main() {
	//Game game(1600, 900);
	//game.Run();
	UserAccount account("NewUser2");
	if (account.CreateAccount("newPassword", "newMe@gmail.com")) {
		std::cout << "Created account!" << std::endl;
	}
	else {
		std::cout << "Failed to create account!" << std::endl;
	}
	system("pause");
}
