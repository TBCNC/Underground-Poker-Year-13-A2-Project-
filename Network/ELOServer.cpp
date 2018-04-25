#include "ELOServer.h"

ELOServer::ELOServer()
{
}

ELOServer::ELOServer(int portNumber)
{
	this->portNumber = portNumber;
	if (this->serverSocket.listen(this->portNumber) != sf::Socket::Done) {
		//Could not start server
		serverOnline = false;
	}
	else {
		std::cout << "ELO Server started." << std::endl;
		serverSelector.add(this->serverSocket);
	}
}

ELOServer::~ELOServer()
{
}

void ELOServer::Start()
{
	while (this->serverOnline) {
		while (this->serverSelector.wait()) {
			if (this->serverSelector.isReady(this->serverSocket)) {
				TcpSocket *newConnection;
				if (this->serverSocket.accept(*newConnection)) {
					std::cout << "Failed to accept an incoming connection." << std::endl;
				}
				else {
					std::cout << "New client accepted. Sending successful connection message." << std::endl;
					std::string msg = "";
					PacketHandler packet(PacketType::SUCCESSFUL_CONNECTION, msg);
					serverSelector.add(*newConnection);
					packet.SendPacket(newConnection);
					tempConnections.push_back(newConnection);
				}
			}
			else {
				for (int c = 0; c < this->tempConnections.size(); c++) {
					Packet data;
					if (this->tempConnections.at(c)->receive(data)!=Socket::Done) {
						if (this->tempConnections.at(c)->receive(data) == Socket::Disconnected) {
							this->tempConnections.erase(tempConnections.begin() + c);
						}
					}
					else {
						PacketHandler packet = PacketHandler::ProcessPacket(data);
						ProcessPacket(packet, c);
					}
				}
				for (int c = 0; c < this->allConnections.size(); c++) {
					Packet data;
					if (this->allConnections.at(c).socket->receive(data) == Socket::Disconnected) {
						RemoveFromGame(this->allConnections.at(c));
						this->allConnections.erase(this->allConnections.begin() + c);
					}
				}
			}
			GameCalculations();
			CheckForStarts();
		}
	}
}
void ELOServer::GameCalculations() {
	for (int c = 0; c < this->allConnections.size(); c++) {
		auto currentConnection = this->allConnections.at(c);
		if (currentConnection.gameIndex == -1) {
			//Need to find them a game.
			bool foundGame = false;
			for (int i = 0; i < this->games.size(); i++) {
				if ((currentConnection.player.eloRank) > this->games.at(i).averageRank-50
					|| ((currentConnection.player.eloRank) < std::abs(this->games.at(i).averageRank + 50))) {
					foundGame = true;
					this->games.at(i).players.push_back(currentConnection);
					UpdateRankAverage(&this->games.at(i));
				}
			}
			if (!foundGame) {
				//Create a new game for the player
				Game newGame;
				newGame.players.push_back(currentConnection);
				newGame.averageRank = currentConnection.player.eloRank;
				this->games.push_back(newGame);
			}
		}
	}
}
void ELOServer::CheckForStarts() {
	for (int c = 0; c < this->games.size(); c++) {
		if (this->games.at(c).players.size() >= MIN_PLAYERS) {
		portNumGen:
			int newPort = rand() % 200000 + 100000;
			if (std::find(this->usedPorts.begin(), this->usedPorts.end(), newPort) != this->usedPorts.end() || newPort==this->portNumber) {
				goto portNumGen;//Port number already exists
			}
			Server *newServer = new Server("", newPort, true);
			std::thread serverThread(&Server::Start, newServer);
			serverThread.detach();//Server started
			std::string ourIP = sf::IpAddress::getPublicAddress().toString();
			PacketHandler compPacket(PacketType::COMP_SERVER_FOUND, ourIP + ":" + std::to_string(newPort));
			for (int i = 0; i < this->games.at(c).players.size(); i++) {
				compPacket.SendPacket(this->games.at(c).players.at(i).socket);
			}
			this->games.erase(this->games.begin() + c);
		}
	}
}
void ELOServer::UpdateRankAverage(Game *game)
{
	game->averageRank = 0;
	for (int c = 0; c < game->players.size(); c++) {
		game->averageRank += ((game->players.at(c).player.eloRank) / game->players.size());
	}
}
void ELOServer::RemoveFromGame(ELOConnection conn)
{
	for (int c = 0; c < this->games.size(); c++) {
		auto allPlayers = this->games.at(c).players;
		for (int i = 0; i < allPlayers.size(); i++) {
			if (allPlayers.at(i).player.user.UID == conn.player.user.UID) {
				allPlayers.erase(allPlayers.begin() + i);
				this->games.at(c).players = allPlayers;
				return;
			}
		}
	}
}

void ELOServer::ProcessPacket(PacketHandler packet, int sourceIndex)
{
	if (packet.type == PacketType::ACCOUNT_EXCHANGE) {
		std::cout << "A connection is sending information." << std::endl;
		UserAccount playerAccount(stoi(packet.payload), true);
		ELOConnection newConnection;
		newConnection.player = Player(playerAccount);
		newConnection.socket = this->tempConnections.at(sourceIndex);
		this->tempConnections.erase(this->tempConnections.begin() + sourceIndex);
		this->allConnections.push_back(newConnection);
	}
}
