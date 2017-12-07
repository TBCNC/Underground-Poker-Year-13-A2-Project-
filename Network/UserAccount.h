#include "DBConnection.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#pragma once

class UserAccount
{
public:
	UserAccount();
	UserAccount(int UID);
	UserAccount(sf::String username, sf::String password);

	static UserAccount RetrieveUserDetails(int UID);
private:
	int ELO;
	sf::String username;
	sf::Image profilePicture;
};