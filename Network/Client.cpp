#include "Client.h"
#include <Windows.h>

Client::Client(int UID) {
	this->UID = UID;
	UserAccount account(UID);
	this->player = Player(account);
}
void Client::ConnectToServer(IpAddress address, int port) {
	if (this->connection.connect(address, port) == Socket::Done) {
		this->listener.add(this->connection);//Connected to the server
		connected = true;
		std::cout << "Connected to server!" << std::endl;
		this->ListenForData();
	}
}
void Client::ListenForData() {
	while (this->connected) {
		if (this->listener.wait()) {
			if (this->listener.isReady(this->connection)) {
				//We have some new data, let's get it now.
				Packet newData;
				std::cout << "Receiving new data!" << std::endl;
				if (this->connection.receive(newData) != Socket::Done) {
					std::cout << "Error?" << std::endl;
				}
				else {
					PacketHandler packet = PacketHandler::ProcessPacket(newData);
					ProcessPacket(packet);
				}
			}
		}
	}
}
void Client::ProcessPacket(PacketHandler packet) {
	PacketType type = packet.type;
	if (type == SERVER_MESSAGE) {
		std::cout << "Message from server:" << packet.payload << std::endl;
	}
	else if (type == SUCCESSFUL_CONNECTION) {
		std::cout << "The server allowed us to connect! Let's send them our info." << std::endl;
		PacketHandler packet(PacketType::ACCOUNT_EXCHANGE,std::to_string(this->UID));
		packet.SendPacket(&this->connection);
		std::cout << "Sent account information." << std::endl;
	}
	else if (type == CHAT_MESSAGE) {

	}
	else if (type == HAND_INFORMATION) {
		std::cout << "Got some cards! Payload:" << packet.payload << std::endl;
	}
	else if (type == MOVE_REQUIRED) {
		std::cout << "You need to make a move!\n[1] Fold\nEnter option:" << std::endl;
		std::string option;
		std::cin >> option;
		if (option == "1") {
			PacketHandler packet(PacketType::MOVE_FOLD, "");
			packet.SendPacket(&this->connection);
			std::cout << "Sent fold request." << std::endl;
		}
	}
}