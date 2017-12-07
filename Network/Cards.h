#include <vector>
#pragma once

enum Suit : int{
	HEARTS=0,
	DIAMONDS=1,
	CLUBS=2,
	SPADES=3,
};
enum Value :int {
	NULLCARD=0,
	ACE=1,
	TWO=2,
	THREE=3,
	FOUR=4,
	FIVE=5,
	SIX=6,
	SEVEN=7,
	EIGHT=8,
	NINE=9,
	TEN=10,
	JACK=11,
	QUEEN=12,
	KING=13,
};
struct Card {
	Suit card_suit;
	Value card_value;
};
struct Hand {
	std::vector<Card> cards;
};