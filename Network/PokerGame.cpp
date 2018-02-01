#include "Server.h"

void Server::StartGame() {
	for (int c = 0; c < playingGame.size(); c++) {
		deal.DealCard(&playingGame.at(c).player);
		deal.DealCard(&playingGame.at(c).player);
		std::string payload = std::to_string(playingGame.at(c).player.hand.cards.at(0).card_suit) + std::to_string(playingGame.at(c).player.hand.cards.at(0).card_value) + ","
			+ std::to_string(playingGame.at(c).player.hand.cards.at(1).card_suit) + std::to_string(playingGame.at(c).player.hand.cards.at(1).card_value);
		PacketHandler packet(PacketType::HAND_INFORMATION, payload);
		packet.SendPacket(playingGame.at(c).socket);
	}
	PacketHandler packet(PacketType::MOVE_REQUIRED, "");
	packet.SendPacket(playingGame.at(currentTurnIndex).socket);
}
bool Server::NextTurn() {
	std::cout << "Carrying out next turn..." << std::endl;
	if (playingGame.size()==1)
		return false;
	if (currentTurnIndex != playingGame.size()) {
		PacketHandler packet(PacketType::MOVE_REQUIRED, "");
		packet.SendPacket(playingGame.at(currentTurnIndex).socket);
		return true;
	}
	else {
		if (this->tableCards.cards.size() != 5) {
			if (startThree) {
				for (int c = 0; c < 3; c++) {
					this->deal.DealCard(&this->tableCards);
				}
				startThree = false;
			}
			else {
				this->deal.DealCard(&this->tableCards);
			}
			std::string fullPayload;
			for (int c = 0; c < this->tableCards.cards.size(); c++) {
				fullPayload += std::to_string(tableCards.cards.at(c).card_suit) + std::to_string(tableCards.cards.at(c).card_value);
				fullPayload += ",";
			}
			PacketHandler packet(PacketType::TABLE_CARDS, fullPayload);
			SendToAll(packet);
			PacketHandler packet2(PacketType::MOVE_REQUIRED, "");
			currentTurnIndex = 0;
			packet2.SendPacket(this->playingGame.at(currentTurnIndex).socket);
		}
		else {
			//Determine winner
			
		}
	}
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