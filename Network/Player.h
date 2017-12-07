#include "Cards.h"
#include "PacketHandler.h"
#include <SFML/System.hpp>
//Also include the database header file when it is done and my database wants to work
#pragma once
class Player {
public:
	void Fold();
	void Call(int points);
	void Raise(int points);
	Hand hand;
private:
	int UID;
	sf::String username;
	sf::TcpSocket connection;
	int points;
	bool playing=true;
	int eloRank;
};
