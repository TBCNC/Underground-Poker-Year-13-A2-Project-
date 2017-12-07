#include <iostream>
#include "PacketHandler.h"
#pragma once

class ClientProcessor {
public:
	 void ProcessPacket(PacketHandler packet) {
		switch (packet.type) {
		case PacketType::SERVER_MESSAGE:
			std::cout << "Message from server:" << packet.payload << std::endl;
			break;
		case PacketType::CHAT_MESSAGE:
			std::cout << packet.payload << std::endl;
			break;
		case PacketType::MOVE_CALL:
			std::cout << "Player " << packet.payload << " decided to call!" << std::endl;
		}
	}
};