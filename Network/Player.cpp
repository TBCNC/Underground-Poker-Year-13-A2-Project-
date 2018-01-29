#include "Player.h"

Player::Player(UserAccount user) {
	this->user = user;
}
void Player::Fold() {
	this->playing = false;
}