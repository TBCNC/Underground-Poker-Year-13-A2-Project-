#include "UserServers.h"

UserServers::UserServers() {

}
std::vector<UserServer> UserServers::GetServers() {
	std::string table = "servers";
	std::vector<std::string> columns = {"SID","Name","Password","IP_Address","Port"};
	DBConnection db;
	std::vector<UserServer> servers;
	std::vector<std::vector<std::string>> results = db.ExecuteQuery_Select(table, columns, {}, {});
	for (int c = 0; c < results.size(); c++) {
		UserServer server;
		server.id = std::stoi(results.at(c).at(0));
		server.name = results.at(c).at(1);
		server.password = results.at(c).at(2);
		if (server.password != "")
			server.passwordProtected = true;
		server.ip = results.at(c).at(3);
		server.port = std::stoi(results.at(c).at(4));
		servers.push_back(server);
	}
	return servers;
}