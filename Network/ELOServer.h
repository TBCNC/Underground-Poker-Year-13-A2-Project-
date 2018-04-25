#include <algorithm>
#include "../Network/DBConnection.h"
#include "../Network/UserAccount.h"
#include "../Network/Player.h"
#include "../Network/Server.h"
#include <iostream>
#include "PacketHandler.h"
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#define MIN_PLAYERS 4
#pragma once

using namespace sf;

struct ELOConnection {
	ELOConnection() :player(Player(UserAccount(0))) {

	}
	TcpSocket* socket;
	Player player;
	int gameIndex = -1;
};
struct Game {
	std::vector<ELOConnection> players;
	float averageRank;
};
class ELOServer {
public:
	ELOServer();
	ELOServer(int portNumber);
	~ELOServer();
	void Start();
private:
	void RemoveFromGame(ELOConnection conn);
	void ProcessPacket(PacketHandler packet, int sourceIndex);
	void GameCalculations();
	void UpdateRankAverage(Game *game);
	void CheckForStarts();
	TcpListener serverSocket;
	SocketSelector serverSelector;
	int portNumber;
	std::vector<Game> games;
	std::vector<int> usedPorts;
	std::vector<ELOConnection> allConnections;
	std::vector<TcpSocket*> tempConnections;
	bool serverOnline;
};