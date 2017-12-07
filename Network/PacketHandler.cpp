#include "PacketHandler.h"

PacketHandler::PacketHandler(PacketType type, std::string payload) {
	this->type = type;
	this->payload = payload;
}
PacketHandler PacketHandler::ProcessPacket(sf::Packet packet)
{
	int type;
	std::string payload;
	packet >> type >> payload;
	PacketHandler returnValue((PacketType)type, payload);
	return returnValue;
}
void PacketHandler::SendPacket(sf::TcpSocket *socket) {
	sf::Packet newPacket;
	int enumValue = (int)this->type;
	newPacket << enumValue << this->payload;
	if (socket->send(newPacket) != sf::Socket::Done) {
		//There has been an error
		printf("Error sending data!\n");
	}
}