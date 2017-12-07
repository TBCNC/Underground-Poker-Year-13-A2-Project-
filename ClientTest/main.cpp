#include <iostream>
#include "../Network/Client.h"

int main() {
	Client client(1);
	client.ConnectToServer("127.0.0.1", 9999);
}