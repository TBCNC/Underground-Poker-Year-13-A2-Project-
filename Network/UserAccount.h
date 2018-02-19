#include "DBConnection.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "PasswordHash.h"
#pragma once

class UserAccount
{
public:
	UserAccount();
	UserAccount(int UID, bool retrieveInfo=false);
	UserAccount(sf::String username);
	bool Login(sf::String password);
	bool UserExist();
	sf::String username;
	int UID = 0;
	int ELO;
	bool CreateAccount(sf::String password,sf::String email);
private:
	sf::String GetPasswordHash();
	std::string GetProfilePicture();
	void RetrieveInformation();
	sf::Image profilePicture;
};