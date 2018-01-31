#include "../Network/Client.h"

int main() {
	std::cout << "Enter UID:";
	std::string uid;
	std::cin >> uid;
	Client client(std::stoi(uid));
	client.ConnectToServer("192.168.0.15", 666);
}