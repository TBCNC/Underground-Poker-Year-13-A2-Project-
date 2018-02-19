#include <iostream>
#include "../Network/Server.h"


int main() {
	Server server("Test server", 666, true);
	server.Start();
}