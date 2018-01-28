#include "Server.h"

void Server::StartGame() {
	for (int c = 0; c < connectedClients.size(); c++) {
		deal.DealCard(&connectedClients.at(c).player);
		deal.DealCard(&connectedClients.at(c).player);
		std::string payload = std::to_string(connectedClients.at(c).player.hand.cards.at(0).card_suit) + std::to_string(connectedClients.at(c).player.hand.cards.at(0).card_value) + ","
			+ std::to_string(connectedClients.at(c).player.hand.cards.at(1).card_suit) + std::to_string(connectedClients.at(c).player.hand.cards.at(1).card_value);
		PacketHandler packet(PacketType::HAND_INFORMATION, payload);
		packet.SendPacket(connectedClients.at(c).socket);
	}
	PacketHandler packet(PacketType::MOVE_REQUIRED, "");
	packet.SendPacket(connectedClients.at(turnCounter).socket);
}
void Server::NextTurn() {
	turnCounter++;
	PacketHandler packet(PacketType::MOVE_REQUIRED, "");
	packet.SendPacket(connectedClients.at(turnCounter).socket);
}