#pragma once
enum PacketType : int {
	ACCOUNT_EXCHANGE = 0,
	CHAT_MESSAGE = 1,
	SERVER_MESSAGE = 2,
	MOVE_FOLD = 3,
	MOVE_CALL = 4,
	MOVE_RAISE = 5,
};

