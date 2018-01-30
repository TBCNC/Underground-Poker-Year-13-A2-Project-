#include "DBConnection.h"
#include <SFML/System.hpp>
#include <vector>
#pragma once
struct UserServer {
	int id;
	sf::String name;
	bool passwordProtected = false;
	sf::String password;
	sf::String ip;
	int port;
};
class UserServers {
public:
	UserServers();
	std::vector<UserServer> GetServers();
};