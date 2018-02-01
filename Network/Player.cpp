#include "Player.h"

Player::Player(UserAccount user) {
	this->user = user;
	this->eloRank = user.ELO;
}
void Player::Fold() {
	this->playing = false;
}
void Player::Call(int points) {
	this->points -= points;
}