#include "DBConnection.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "PasswordHash.h"
#pragma once

class UserAccount
{
public:
	UserAccount();
	UserAccount(int UID);
	UserAccount(sf::String username);
	bool Login(sf::String password);
	void CreateAccount();
private:
	sf::String GetPasswordHash();
	int UID=0;
	bool UserExist();
	void RetrieveInformation();
	int ELO;
	sf::String username;
	sf::Image profilePicture;
};