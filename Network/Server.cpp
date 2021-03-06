#include "Server.h"

Server::Server()
{
}

Server::Server(std::string name, int portNum, bool competitive, std::string password){
	this->name = name;
	this->port = portNum;
	this->password = password;
	this->competitive = competitive;
	if (this->serverSocket.listen(portNum) != sf::Socket::Done) {
		//Something has gone wrong.
		serverOnline = false;
	}
	else {
		//Using cout for debugging only
		std::cout << "Server has started. Adding to database and listening for new connections." << std::endl;
		if (!competitive) {
			DBConnection db;
			if(strlen(password.c_str())>0)
				db.ExecuteQuery_Insert("servers", { "name","password","ip_address","port" }, { this->name,PasswordHash::GeneratePassword(this->password),sf::IpAddress::getPublicAddress().toString(),std::to_string(this->port) });
			else
				db.ExecuteQuery_Insert("servers", { "name","ip_address","port" }, { this->name,sf::IpAddress::getPublicAddress().toString(),std::to_string(this->port) });
		}
		serverSelector.add(this->serverSocket);
	}
}
Server::~Server() {
	//Create a delete functino for dbconnection and use it here
	std::cout << "Deleting!" << std::endl;
	DBConnection db;
	db.ExecuteQuery_Delete("servers", { "ip_address" }, { sf::IpAddress::getPublicAddress().toString() });

}
void Server::Start() {
	while (this->serverOnline) {
		if (this->serverSelector.wait()) {
			
			if (this->serverSelector.isReady(this->serverSocket)) {
				TcpSocket *newClient = new TcpSocket;
				if (this->serverSocket.accept(*newClient) != Socket::Done) {
					//Error accepting them
				}
				else {
					if (this->currentPlayers < MAX_PLAYERS) {
						//Accept the connection
						std::cout << "New client accepted. Sending successful connection message..." << std::endl;
						std::string message = "";
						PacketHandler packet(PacketType::SUCCESSFUL_CONNECTION, message);
						serverSelector.add(*newClient);
						this->currentPlayers++;
						packet.SendPacket(newClient);
						UserAccount account(0);
						Connection newConn;
						newConn.player = Player(account);
						newConn.socket = newClient;
						connectedClients.push_back(newConn);
					}
					else {
						newClient->disconnect();
					}
				}
			}
			else {
				for (int c = 0; c < this->connectedClients.size(); c++) {
					if (this->serverSelector.isReady(*this->connectedClients.at(c).socket)) {
						std::cout << "New data!" << std::endl;
						Packet data;
						if (this->connectedClients.at(c).socket->receive(data) != Socket::Done) {
							if (this->connectedClients.at(c).socket->receive(data) == Socket::Disconnected) {
								std::cout << this->connectedClients.at(c).player.user.username.toAnsiString() << " disconnected." << std::endl;
								if (!gameOnline) {
									connectedClients.erase(connectedClients.begin() + c);
									playingGame.erase(playingGame.begin() + c);
								}
								else {
									Connection conn = connectedClients.at(c);
									for (int i = 0; c < playingGame.size(); i++) {
										if (conn.socket == playingGame.at(i).socket) {
											if (currentTurnIndex == i) {
												currentTurnIndex++;
												if (NextTurn()) {
													std::cout << "Waiting for next turn..." << std::endl;
												}
												else {
													//Determine winner
												}
											}
											playingGame.erase(playingGame.begin() + i);
											break;
										}
									}
									connectedClients.erase(connectedClients.begin() + c);
								}
								std::string payload = "";
								for (int c = 0; c < this->connectedClients.size(); c++) {
									payload += std::to_string(connectedClients.at(c).player.user.UID);
									payload += ",";
								}
								PacketHandler packetToSend(ALL_PLAYERS, payload);
								SendToAll(packetToSend);
							}
						}
						else {
							PacketHandler packet = PacketHandler::ProcessPacket(data);
							ProcessPacket(packet,c);
						}
					}
				}
			}
			
		}
	}
}
void Server::ProcessPacket(PacketHandler packet,int sourceIndex) {
	auto type = packet.type;
	if (type == PacketType::ACCOUNT_EXCHANGE) {
		std::cout << "A recently connected client wants to send their data." << std::endl;
		UserAccount playerAccount(stoi(packet.payload),true);
		this->connectedClients.at(sourceIndex).player = Player(playerAccount);
		if (!gameOnline) {
			playingGame.push_back(connectedClients.at(sourceIndex));
		}
		std::cout << "Account added! Their username is " << connectedClients.at(sourceIndex).player.user.username.toAnsiString() << std::endl;
		std::cout << "Sending player list to all clients..." << std::endl;
		std::string payload = "";
		for (int c = 0; c < this->connectedClients.size(); c++) {
			payload += std::to_string(connectedClients.at(c).player.user.UID);
			payload += ",";
		}
		PacketHandler packetToSend(PacketType::ALL_PLAYERS, payload);
		SendToAll(packetToSend); 
		if (this->currentPlayers >= 2 && !gameOnline) {
			std::cout << "Starting game!" << std::endl;
			PacketHandler packetToSend(PacketType::SERVER_MESSAGE, "The game is about to start!");
			SendToAll(packetToSend);
			gameOnline = true;
			startThree = true;
			currentTurnIndex = 0;
			StartGame();
		}
	}
	else if (type == PacketType::CHAT_MESSAGE) {
		std::string fullMsg = this->connectedClients.at(sourceIndex).player.user.username.toAnsiString() + ":" + packet.payload;
		PacketHandler packetToSend(PacketType::CHAT_MESSAGE, fullMsg);
		SendToAll(packetToSend);
	}
	else if (type == PacketType::MOVE_FOLD) {
		std::cout << this->connectedClients.at(sourceIndex).player.user.username.toAnsiString() << " wants to fold!" << std::endl;
		PerformFold(&this->connectedClients.at(sourceIndex).player);
		PacketHandler packetToSend(PacketType::SERVER_MESSAGE, this->connectedClients.at(sourceIndex).player.user.username.toAnsiString() + " has folded!");
		PacketHandler summationPacket(PacketType::MOVE_FOLD, std::to_string(this->connectedClients.at(sourceIndex).player.user.UID));
		SendToAll(packetToSend, connectedClients.at(sourceIndex));//Let everyone know a player has folded
		SendToAll(summationPacket);
		if (NextTurn()) {
			std::cout << "Waiting for next turn..." << std::endl;
		}
		else {
			std::cout << "The round is now over." << std::endl;
			currentTurnIndex++;
			std::cout << "The winner is " << playingGame.at(currentTurnIndex-1).player.user.username.toAnsiString() << std::endl;
			PacketHandler winnerPacket(PacketType::SERVER_MESSAGE, "Round over! The winner of this round is " + playingGame.at(currentTurnIndex-1).player.user.username.toAnsiString());
			SendToAll(winnerPacket);
			sf::sleep(sf::seconds(3));
			std::cout << "Starting new game..." << std::endl;
			ResetPlayers();
			StartGame();
		}
	}
	else if (type == PacketType::MOVE_CALL) {
		std::cout << this->connectedClients.at(sourceIndex).player.user.username.toAnsiString() << " wants to call!" << std::endl;
		PerformCall(&this->connectedClients.at(sourceIndex).player,stoi(packet.payload));
		PacketHandler callPacket(PacketType::MOVE_CALL, std::to_string(this->connectedClients.at(sourceIndex).player.user.UID) + "," +packet.payload);
		SendToAll(callPacket);
		PacketHandler packetToSend(PacketType::SERVER_MESSAGE, this->connectedClients.at(sourceIndex).player.user.username.toAnsiString() + " has called (" + packet.payload + " points)!");
		SendToAll(packetToSend, this->connectedClients.at(sourceIndex));
		if (NextTurn()) {
			std::cout << "Waiting for next turn..." << std::endl;
		}
		else {
			std::cout << "The round is now over." << std::endl;
			std::cout << "The winner is " << this->winner.player.user.username.toAnsiString() << std::endl;
			PacketHandler winnerPacket(PacketType::SERVER_MESSAGE, "Round over! The winner of this round is " + playingGame.at(currentTurnIndex - 1).player.user.username.toAnsiString());
			SendToAll(winnerPacket);
			sf::sleep(sf::seconds(3));
			std::cout << "Starting new game..." << std::endl;
			ResetPlayers();
			StartGame();
		}
	}
}
void Server::SendToAll(PacketHandler packet, Connection exclusion) {
	for (int c = 0; c < connectedClients.size(); c++) {
		if (connectedClients.at(c).socket != exclusion.socket) {
			packet.SendPacket(connectedClients.at(c).socket);
		}
	}
}
void Server::ResetPlayers() {
	this->playingGame.clear();
	this->tableCards.cards.clear();
	for (int c = 0; c < connectedClients.size(); c++) {
		this->playingGame.push_back(connectedClients.at(c));
		this->connectedClients.at(c).player.hand.cards.clear();
	}
}