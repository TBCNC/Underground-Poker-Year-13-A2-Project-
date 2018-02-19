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
	void ConnectToServer(IpAddress address, int port);
	void SendPacketToServer(PacketType type, std::string payload); 
	Player player = Player(UserAccount(1));//Need this initializer to prevent crashing
	std::vector<ClientEvent> events;
private:
	TcpSocket connection;
	SocketSelector listener;
	void AddEvent(PacketType type, std::string payload);
	void ProcessPacket(PacketHandler packet);
	void ListenForData();
	bool connected=false;
	int UID;
	bool firstPlayerList = true;
	std::vector<Player> enemies;
};
