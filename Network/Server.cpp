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
			if (this->serverSelector.isReady(this->serverSocket)) {
				TcpSocket *newClient = new TcpSocket;
				if (this->serverSocket.accept(*newClient) != Socket::Done) {
					//Error accepting him
				}
				else {
					if (this->currentPlayers < MAX_PLAYERS) {
						//Accept the connection
						std::cout << "We got a new client! Sending them data..." << std::endl;
						std::string message = "Welcome to our server\0";
						PacketHandler packet(PacketType::SERVER_MESSAGE, message);
						packet.SendPacket(newClient);
						std::cout << "Data sent!" << std::endl;
					}
					else {
						newClient->disconnect();
					}
				}
			}
			else {
				for (int c = 0; c < this->connectedClients.size(); c++) {
					if (this->serverSelector.isReady(*this->connectedClients.at(c))) {
						//We have some new data, let's process it.
						Packet data;
						if (this->connectedClients.at(c)->receive(data) != Socket::Done) {
							//Something went wrong
						}
						else {
							std::string message;
							data >> message;
							std::cout << "The message was:" << message << std::endl;
						}
					}
				}
			}
		}
	}
}
