#include "Client.h"

Client::Client(int UID) {
	this->UID = UID;
}
void Client::ConnectToServer(IpAddress address, int port) {
	if (this->connection.connect(address, port) == Socket::Done) {
		this->listener.add(this->connection);//Connected to the server
		connected = true;
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
					//error
					std::cout << "Error?" << std::endl;
				}
				else {
					PacketHandler packet = PacketHandler::ProcessPacket(newData);
					ClientProcessor processor;
					processor.ProcessPacket(packet);
				}
			}
		}
	}
}