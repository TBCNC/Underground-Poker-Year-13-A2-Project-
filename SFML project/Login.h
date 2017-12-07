#include "../Network/Player.h"
#include "../Network/Client.h"
//Other includes will be "included" here once they have been made.
#pragma once

class Login {
public:
	Login(sf::String username, sf::String password);
private:
	void CheckCredentials();
	sf::String username;
	sf::String password;
};
