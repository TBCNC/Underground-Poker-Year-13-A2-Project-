#include "DBConnection.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "PasswordHash.h"
#pragma once

struct Statistics {
	int rounds_won;
	int rounds_lost;
	int games_won;
	int games_lost;
	int comps_won;
	int comps_lost;
	float wintoloss_games;
	float wintoloss_comps;
};
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
	Statistics userStats;
private:
	sf::String GetPasswordHash();
	std::string GetProfilePicture();
	void RetrieveInformation();
};