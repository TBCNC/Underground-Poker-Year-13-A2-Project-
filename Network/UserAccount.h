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
	UserAccount(sf::String username, bool retrieveInfo=true);
	bool Login(sf::String password);
	bool UserExist();
	sf::String username;
	int UID = 0;
	int ELO;
	bool CreateAccount(sf::String password,sf::String email);
	std::string profilePicture;//Location of profile pic texture
private:
	sf::String GetPasswordHash();
	std::string GetProfilePicture();
	void RetrieveInformation();
};