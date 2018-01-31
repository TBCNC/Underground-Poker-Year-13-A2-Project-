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
bool Server::RoundOver() {//Check whether the round is over due to folds
	int foldCount = 0;
	for (int c = 0; c < playingGame.size(); c++) {
		if (!playingGame.at(c).player.playing)
			foldCount++;
	}
	return foldCount == playingGame.size() - 2;
}
bool Server::NextTurn() {
	if (RoundOver())
		return false;
	PacketHandler packet(PacketType::MOVE_REQUIRED, "");
	packet.SendPacket(playingGame.at(currentTurnIndex).socket);
	return true;
}
void Server::PerformFold(Player *player) {
	player->Fold();
	this->playingGame.erase(this->playingGame.begin() + currentTurnIndex);
}
void Server::PerformCall(Player *player, int callAmount) {
	player->Call(callAmount);
	currentTurnIndex++;
}
void Server::PerformRaise(Player *player, int callAmount) {
	player->Call(callAmount);
	this->minCall = callAmount;
	currentTurnIndex++;
}