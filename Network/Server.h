#pragma once
#include "../Network/DBConnection.h"
#include "../Network/PasswordHash.h"
#include "Dealer.h"
#include <iostream>
#include "PacketHandler.h"
#include "Player.h"
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#ifndef SERVER_H
#define SERVER_H

#define MAX_PLAYERS 8

using namespace sf;

enum GameType : int{
	DEBUG=0,
	TEXAS_HOLD_EM=1,
};
struct Connection {
	TcpSocket* socket;
	Player player = Player(UserAccount(0));
};
class Server {
public:
	Server(std::string name, int portNum, bool competitive=false, std::string password="");
	~Server();
	void Start();
	//std::map<TcpSocket*, Player> connectedClients;
	std::vector<Connection> connectedClients;
	int currentPlayers = 0;
	void AddToDB();
	void StartGame();
	bool NextTurn();
	void PerformFold(Player *player);
	void PerformCall(Player *player, int callAmount);
	void PerformRaise(Player *player, int raiseAmount);
	bool GameOver();

private:
	TcpListener serverSocket;
	SocketSelector serverSelector;
	bool serverOnline = true;
	bool gameOnline = false;
	void SendToAll(PacketHandler packet, Connection exclusion);
	void ProcessPacket(PacketHandler packet, int sourceIndex);
	int OutCounter();
	int turnCounter = 0;//When this reaches the length of the list-outcounter, all players have played and we deal out more cards.
	int currentTurnIndex = 0;
	int totalJackpot = 0;
	bool competitive = false;
	Dealer deal = Dealer(52);
	std::string name;
	std::string password;
	int port;
};

#endif // !