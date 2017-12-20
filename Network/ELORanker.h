#include <iostream>
#include <iomanip>
#include "Player.h"
#include <vector>
#pragma once
///<summary>
///This class is designed for use after the end of a game/match in order to determine the new ranks of the winners and the losers.
///</summary>
enum GameRanks : int{
	Unranked=0,
	Copper_1=1,
	Copper_2=2,
	Copper_3=3,
	Copper_4=4,
	Copper_5=5,
	Bronze_1=6,
	Bronze_2=7,
	Bronze_3=8,
	Bronze_4=9,
	Bronze_5=10,
	Silver_1=11,
	Silver_2=12,
	Silver_3=13,
	Silver_4=14,
	Silver_5=15,
	Gold_1=16,
	Gold_2=17,
	Gold_3=18,
	Gold_4=19,
	Gold_5=20,
	Diamond_1=21,
	Diamond_2=22,
	Diamond_3=23,
	Diamond_4=24,
	Diamond_5=25,
	Ruby_1=26,
	Ruby_2=27,
	Ruby_3=28,
	Ruby_4=29,
	Ruby_5=30
};
class ELORanker {
public:
	ELORanker(Player *our_player, std::vector<Player*> enemy_players);
	double CalculatELORank(double final_score);
	int CalculateGameRank(double rank_elo);
private:
	double CalculateExpectedScore();
	Player *our_player;
	std::vector<Player*> enemy_players;
};
