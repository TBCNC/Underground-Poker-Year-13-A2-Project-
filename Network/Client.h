#include <iostream>
#include <SFML/Network.hpp>
#include "Player.h"
#include "PacketHandler.h"
#include <sstream>
#include <thread>
#pragma once

using namespace sf;
struct ClientEvent{
	PacketType type;
	std::string payload;
};
class Client {
public:
	Client();
	Client(int UID);
	bool ConnectToServer(IpAddress address, int port);
	void SendPacketToServer(PacketType type, std::string payload);
	void ListenForData();
	Player player = Player(UserAccount(1));//Need this initializer to prevent crashing
	std::vector<ClientEvent> events;
	std::vector<Player> enemies;
private:
	int UID;
	TcpSocket connection;
	SocketSelector listener;
	void AddEvent(PacketType type, std::string payload);
	void ProcessPacket(PacketHandler packet);
	bool connected=false;
	bool firstPlayerList = true;
};
