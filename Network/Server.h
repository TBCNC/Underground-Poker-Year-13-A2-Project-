#include <iostream>
#include "PacketHandler.h"
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#ifndef SERVER_H
#define SERVER_H

#define MAX_PLAYERS 8

using namespace sf;

class Server {
public:
	Server(int portNum);
	void Start();
private:
	TcpListener serverSocket;
	SocketSelector serverSelector;
	std::vector<TcpSocket*> connectedClients;
	int currentPlayers=0;
	bool serverOnline = true;
};

#endif // !