#include <iostream>
#include <SFML/Network.hpp>
#include "Player.h"
#include "PacketHandler.h"
#pragma once

using namespace sf;

class Client {
public:
	Client(int UID);
	void ConnectToServer(IpAddress address, int port);
private:
	TcpSocket connection;
	SocketSelector listener;
	void ProcessPacket(PacketHandler packet);
	void ListenForData();
	bool connected=false;
	Player player=Player(UserAccount(0));//Need this initializer to prevent crashing
	int UID;
};
