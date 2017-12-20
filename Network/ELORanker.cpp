#include "ELORanker.h"

ELORanker::ELORanker(Player *our_player, std::vector<Player> enemy_players) {
	this->our_player = our_player;
	this->enemy_players = enemy_players;
}
float ELORanker::CalculateExpectedScore() {
	float expected_score = 0;
	for (int c = 0; c < this->enemy_players.size(); c++) {
		expected_score += 1 / (1 + pow(10, (enemy_players.at(c).eloRank - this->our_player->eloRank) / 400));
	}
	return expected_score;
}
float ELORanker::CalculatELORank(float final_score){
	return this->our_player->eloRank + (5 * (final_score - this->CalculateExpectedScore()));
}
int ELORanker::CalculateGameRank(float rank_elo) {
	if (rank_elo < 30) {
		return GameRanks::Unranked;
	}
	else {
		return floor(((this->our_player->eloRank / GameRanks::Ruby_5) * 31)-1);
	}
}