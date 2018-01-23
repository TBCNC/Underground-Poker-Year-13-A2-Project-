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
	bool Login();
private:
	void RetrieveInformation(int UID);
	void RetrieveInformation(sf::String username);
	sf::String GetPasswordHash();
	int ELO;
	sf::String username;
	sf::Image profilePicture;
};