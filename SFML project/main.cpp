//#include "Game.h"
//#include "../Network/DBConnection.h"
#include <iostream>
#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	/*
	DBConnection database_connection;
	std::vector<std::string> testVector1;
	testVector1.push_back("Username");
	testVector1.push_back("Password");
	testVector1.push_back("Email");
	std::vector<std::string> testVector2;
	testVector2.push_back("newUser");
	testVector2.push_back("weeabooJones");
	testVector2.push_back("newEmail");
	database_connection.ExecuteQuery_Insert("users", testVector1, testVector2);
	system("pause");
	*/
	
	Player *our_player = new Player;
	our_player->eloRank = 240;
	Player *enemy_player1 = new Player, *enemy_player2 = new Player, *enemy_player3 = new Player;
	enemy_player1->eloRank = 210;
	enemy_player2->eloRank = 243;
	enemy_player3->eloRank = 223;
	std::vector<Player*> enemies;
	enemies.push_back(enemy_player1); enemies.push_back(enemy_player2); enemies.push_back(enemy_player3);
	ELORanker ranker(our_player, enemies);
	float newRank = ranker.CalculatELORank(1);
	std::cout << "Previous ELO rank:" << our_player->eloRank << std::endl;
	std::cout << "New ELO rank:" << newRank << std::endl;
	std::cout << "Determined game rank:" << ranker.CalculateGameRank(newRank)<< std::endl;
	system("pause");
	
}
 