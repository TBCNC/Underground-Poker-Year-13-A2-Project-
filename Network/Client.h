#include "ClientProcessor.h"
#include <iostream>
#include <SFML/Network.hpp>
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
	void ListenForData();
	bool connected=false;
	int UID;
};
