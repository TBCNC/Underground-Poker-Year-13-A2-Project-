//#include "../Network/UserAccount.h"
#include <iostream>
#include "../Network/UserAccount.h"
#include "../Network/Server.h"
#include "../Network/PokerRanker.h"

int main() {
	Server server("newServer", 666, false, "abc123");
	server.Start();
}
