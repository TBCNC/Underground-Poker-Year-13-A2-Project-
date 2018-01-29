#include "DBConnection.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "PasswordHash.h"
#pragma once

class UserAccount
{
public:
	UserAccount();
	UserAccount(int UID);
	UserAccount(sf::String username);
	bool Login(sf::String password);
	bool UserExist();
	bool CreateAccount(sf::String password,sf::String email);
private:
	sf::String GetPasswordHash();
	int UID=0;
	void RetrieveInformation();
	int ELO;
	sf::String username;
	sf::Image profilePicture;
};