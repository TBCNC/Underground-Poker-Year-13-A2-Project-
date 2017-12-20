#include "ELORanker.h"

ELORanker::ELORanker(Player *our_player, std::vector<Player*> enemy_players) {
	this->our_player = our_player;
	this->enemy_players = enemy_players;
}
double ELORanker::CalculateExpectedScore() {
	double expected_score = 0.000000000000;
	for (int c = 0; c < this->enemy_players.size(); c++) {
		double power = (this->enemy_players.at(c)->eloRank - this->our_player->eloRank);
		std::cout << power / 400 << std::endl;
		std::cout << power << std::endl;
		expected_score += (1 / (1 + pow(10,power/400)));
	}
	std::cout << "Expected score:" << expected_score << std::endl;
	return expected_score;
}
double ELORanker::CalculatELORank(double final_score){
	return this->our_player->eloRank + (5 * (final_score - this->CalculateExpectedScore()));
}
int ELORanker::CalculateGameRank(double rank_elo) {
	if (rank_elo < 30) {
		return GameRanks::Unranked;
	}
	else {
		return floor(((this->our_player->eloRank / GameRanks::Ruby_5) * 31)-1);
	}
}
