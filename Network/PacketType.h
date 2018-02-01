#pragma once
enum PacketType : int {
	ACCOUNT_EXCHANGE = 0,
	CHAT_MESSAGE = 1,
	SERVER_MESSAGE = 2,
	MOVE_FOLD = 3,
	MOVE_CALL = 4,
	MOVE_RAISE = 5,
	SUCCESSFUL_CONNECTION=6,
	SERVER_FULL=7,
	SERVER_INFORMATION_REQUIRED=8,
	MOVE_REQUIRED=9,
	HAND_INFORMATION=10,
	ALL_PLAYERS=11,
	TABLE_CARDS=12,
};

