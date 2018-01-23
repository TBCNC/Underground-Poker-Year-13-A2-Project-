#include "../Network/DBConnection.h"
//#include "Game.h"
#include "../Network/PasswordHash.h"
#include "../Network/Cards.h"
#include <iostream>
//#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	std::cout << PasswordHash::EncodeHash("password") << std::endl;
	system("pause");
}
 