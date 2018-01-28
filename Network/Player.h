#include "Cards.h"
#include "PacketHandler.h"
#include "UserAccount.h"
#include <SFML/System.hpp>
//Also include the database header file when it is done and my database wants to work
#pragma once
class Player {
public:
	Player();
	Player(UserAccount user);
	void Fold();
	void Call(int points);
	void Raise(int points);
	int eloRank;
	Hand hand;
private:
	UserAccount user;
	int points;
	bool playing=true;
};
