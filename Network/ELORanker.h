#include "Player.h"
#include <vector>
#pragma once
///<summary>
///This class is designed for use after the end of a game/match in order to determine the new ranks of the winners and the losers.
///</summary>
enum GameRanks : int{
	Unranked=0,
	Copper_1=30,
	Copper_2=45,
	Copper_3=60,
	Copper_4=75,
	Copper_5=90,
	Bronze_1=105,
	Bronze_2=120,
	Bronze_3=135,
	Bronze_4=150,
	Bronze_5=165,
	Silver_1=180,
	Silver_2=195,
	Silver_3=210,
	Silver_4=225,
	Silver_5=240,
	Gold_1=255,
	Gold_2=270,
	Gold_3=285,
	Gold_4=300,
	Gold_5=315,
	Diamond_1=330,
	Diamond_2=345,
	Diamond_3=360,
	Diamond_4=375,
	Diamond_5=390,
	Ruby_1=405,
	Ruby_2=420,
	Ruby_3=435,
	Ruby_4=450,
	Ruby_5=465

};
class ELORanker {
public:
	ELORanker(Player *our_player, std::vector<Player> enemy_players);
	float CalculatELORank(float final_score);
	int CalculateGameRank(float rank_elo);
private:
	float CalculateExpectedScore();
	Player *our_player;
	std::vector<Player> enemy_players;
};
