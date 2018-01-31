#include "../Network/Client.h"

int main() {
	Client client(1);
	client.ConnectToServer("192.168.0.15", 666);
}