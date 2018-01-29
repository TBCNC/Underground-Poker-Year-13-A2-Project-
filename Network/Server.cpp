#include "Server.h"

Server::Server(int portNum){
	if (this->serverSocket.listen(portNum) != sf::Socket::Done) {
		//Something has gone wrong.
		serverOnline = false;
	}
	else {
		//Using cout for debugging only
		std::cout << "Server has started. Listening for new connections." << std::endl;
		serverSelector.add(this->serverSocket);
	}
}
void Server::Start() {
	while (this->serverOnline) {
		if (this->serverSelector.wait()) {
			if (this->currentPlayers >= 2 && !gameOnline) {
				std::cout << "Starting game!" << std::endl;
				gameOnline = true;
				StartGame();
			}
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
						//connectedClients.insert(std::pair<TcpSocket*, Player>(newClient, Player(account)));
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
							std::cout << "ERROR: There was an error recieving data from this socket." << std::endl;
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
		UserAccount playerAccount(stoi(packet.payload));
		this->connectedClients.at(sourceIndex).player = Player(playerAccount);
		std::cout << "Account added! Their UID is " << packet.payload << std::endl;
	}
	else if (type == PacketType::MOVE_FOLD) {
		std::cout << "Player wants to fold!" << std::endl;
		PerformFold(&this->connectedClients.at(sourceIndex).player);
		PacketHandler packetToSend(PacketType::SERVER_MESSAGE, "A player has folded!");
		SendToAll(packetToSend, connectedClients.at(sourceIndex));//Let everyone know a player has folded
		retry:
		if ((turnCounter+1) != connectedClients.size()) {
			if (!NextTurn()) {
				goto retry;
			}
		}
		else {
			PacketHandler packetOver(PacketType::SERVER_MESSAGE, "We're all out of turns!");
			Connection connect;
			SendToAll(packetOver,connect);
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