#include <algorithm>
#include <iostream>
#include "Cards.h"
#pragma once
///<summary>Ranks hands for Texas Hold'Em games.</summary>
enum HandTypes : int{
	ROYAL_FLUSH=0,
	STRAIGHT_FLUSH=1,
	FOUR_OF_A_KIND=2,
	FULL_HOUSE=3,
	FLUSH=4,
	STRAIGHT=5,
	THREE_OF_A_KIND=6,
	TWO_PAIR=7,
	PAIR=8,
	HIGH=9
};
class PokerRanker {
public:
	PokerRanker(Hand hand);
	HandTypes RankHand();
private:
	int DetermineSuitAmount(Suit suit);
	int DetermineValueAmount(Value value);
	bool DetermineStraight();
	int GetPairAmount();
	Hand SortCards();
	Hand hand;
};