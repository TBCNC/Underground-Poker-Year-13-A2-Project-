#include "Client.h"
#include <Windows.h>

Client::Client()
{
}

Client::Client(int UID) {
	this->UID = UID;
	UserAccount account(UID,true);
	this->player = Player(account);
	std::cout << "Client is using UID " << UID << std::endl;
}

void Client::ConnectToServer(IpAddress address, int port) {
	if (this->connection.connect(address, port) == Socket::Done) {
		this->listener.add(this->connection);//Connected to the server
		connected = true;
		std::cout << "Connected to server!" << std::endl;
		ListenForData();
	}
}
void Client::SendPacketToServer(PacketType type, std::string payload)
{
	PacketHandler packetToSend(type, payload);
	packetToSend.SendPacket(&this->connection);
}
void Client::ListenForData() {
	while (this->connected) {
		if (this->listener.wait()) {
			if (this->listener.isReady(this->connection)) {
				//We have some new data, let's get it now.
				Packet newData;
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
void Client::AddEvent(PacketType type, std::string payload) {
	ClientEvent event;
	event.type = type;
	event.payload = payload;
	this->events.push_back(event);
}
void Client::ProcessPacket(PacketHandler packet) {
	PacketType type = packet.type;
	std::string data = packet.payload;
	if (type == SERVER_MESSAGE) {
		std::cout << "Message from server:" << packet.payload << std::endl;
		AddEvent(packet.type, packet.payload);
	}
	else if (type == SUCCESSFUL_CONNECTION) {
		std::cout << "The server allowed us to connect! Let's send them our info." << std::endl;
		PacketHandler packet(PacketType::ACCOUNT_EXCHANGE,std::to_string(this->UID));
		packet.SendPacket(&this->connection);
		std::cout << "Sent account information." << std::endl;
		std::cout << "Adding account information to class..." << std::endl;
		this->player = Player(UserAccount(this->UID));
		AddEvent(packet.type, packet.payload);
	}
	else if (type == ALL_PLAYERS) {
		//std::cout << "Got player list" << std::endl;
		std::stringstream stream(packet.payload);
		std::string item;
		std::vector<std::string> uids;
		while (getline(stream, item, ',')) {
			//std::cout << "Adding:" << item << std::endl;
			uids.push_back(item);
		}
		for (int c = 0; c < uids.size(); c++) {
			if(uids.at(c)!="")
				if(stoi(uids.at(c)) != this->UID)
					this->enemies.push_back(Player(UserAccount(stoi(uids.at(c)),true)));
		}
		if (this->firstPlayerList)
			firstPlayerList = false;
		else
			if(this->enemies.size()!=0)
				std::cout << this->enemies.at(enemies.size()-1).user.username.toAnsiString() << " connected!" << std::endl;
		AddEvent(packet.type, packet.payload);
	}
	else if (type == CHAT_MESSAGE) {
		AddEvent(packet.type, packet.payload);
	}
	else if (type == HAND_INFORMATION) {
		std::cout << "Got some cards! Payload:" << packet.payload << std::endl;
		AddEvent(packet.type, packet.payload);
	}
	else if (type == MOVE_REQUIRED) {
		AddEvent(packet.type, packet.payload);
	}
	else if (type == TABLE_CARDS) {
		std::cout << "Cards on table:" << packet.payload << std::endl;
		AddEvent(packet.type, packet.payload);
	}
}