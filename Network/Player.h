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
	int eloRank;
	Hand hand;
	bool playing = true;
	UserAccount user;
	int points;
private:
};
