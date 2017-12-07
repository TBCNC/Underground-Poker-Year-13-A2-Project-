#include <SFML/Network.hpp>
#include "PacketType.h"
#pragma once
//Add more to these later on


class PacketHandler {
public:
	PacketHandler(PacketType type, std::string payload);
	static PacketHandler ProcessPacket(sf::Packet packet);
	void SendPacket(sf::TcpSocket *socket);
	PacketType type;
	std::string payload;
};
