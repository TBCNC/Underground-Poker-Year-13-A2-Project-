#include "PokerRanker.h"
PokerRanker::PokerRanker(Hand hand) {
	this->hand = hand;
}
HandTypes PokerRanker::RankHand() {
	
	bool flush = false;
	int maxOfSameValue = 0;
	Value maxValue=(Value)0;
	for (int c = 0; c < 3; c++) {
		if (DetermineSuitAmount((Suit)c) >= 5)
			flush = true;
	}
	for (int i = 0; i < this->hand.cards.size(); i++) {
		if (maxValue != this->hand.cards.at(i).card_value) {
			int value = DetermineValueAmount(this->hand.cards.at(i).card_value);
			if (value > maxOfSameValue) {
				maxOfSameValue = value;
				maxValue = this->hand.cards.at(i).card_value;
			}
		}
	}
	if (flush) {
		if (DetermineStraight()) {
			if (DetermineValueAmount(Value::ACE) == 1 && DetermineValueAmount(Value::KING) == 1) {
				//Royal flush
				return HandTypes::ROYAL_FLUSH;
			}
			else {
				return HandTypes::STRAIGHT_FLUSH;
			}
		}
		else {
			return HandTypes::FLUSH;
		}
			
	}
	else {
		if (maxOfSameValue == 4)
			return HandTypes::FOUR_OF_A_KIND;
		if (maxOfSameValue == 3 && GetPairAmount() >= 1) 
			return HandTypes::FULL_HOUSE;
		if (DetermineStraight()) 
			return HandTypes::STRAIGHT;
		if (maxOfSameValue == 3)
			return HandTypes::THREE_OF_A_KIND;
		if (GetPairAmount() == 2)
			return HandTypes::TWO_PAIR;
		if (GetPairAmount() == 1)
			return HandTypes::PAIR;
	}
	return HandTypes::HIGH;
	
}
///<summary>This function sorts the cards in numerical order from lowest to highest</summary>
Hand PokerRanker::SortCards() {
	Hand handClone = this->hand;
	for (int c = 1; c < handClone.cards.size(); c++) {
		Card element = hand.cards.at(c);
		int i = c;
		while (i > 0 && handClone.cards.at(i - 1).card_value > element.card_value) {
			handClone.cards.at(i) = handClone.cards.at(i - 1);
			i--;
		}
		handClone.cards.at(i) = element;
	}
	return handClone;
}
int PokerRanker::GetPairAmount() {
	std::vector<Value> cardPairs;
	for (int c = 0; c < this->hand.cards.size(); c++) {
		if (std::find(cardPairs.begin(), cardPairs.end(), this->hand.cards.at(c).card_value)==cardPairs.end()) {//Is this card value already in vector?
			if (DetermineValueAmount(this->hand.cards.at(c).card_value) == 2) {
				cardPairs.push_back(this->hand.cards.at(c).card_value);
			}
		}
	}
	return cardPairs.size();
}
bool PokerRanker::DetermineStraight() {
	Hand newHand = SortCards();
	for (int c = 0; c < newHand.cards.size()-3; c++) {
		if (newHand.cards.at(c).card_value == Value::ACE) {
			if (newHand.cards.at(c + 1).card_value == Value::TEN || newHand.cards.at(c + 1).card_value == Value::TWO)
				continue;

		}
		if (newHand.cards.at(c).card_value != Value::KING) {
			if (newHand.cards.at(c).card_value != (newHand.cards.at(c + 1).card_value) - 1) {
				return false;
			}
		}
		else {
			if (newHand.cards.at(c + 1).card_value != 0)
				return false;
		}
	}
	return true;
}
int PokerRanker::DetermineSuitAmount(Suit suit) {
	int suitCounter = 0;
	for (int c = 0; c < this->hand.cards.size(); c++) {
		if (this->hand.cards.at(c).card_suit == suit)
			suitCounter++;
	}
	return suitCounter;
}
int PokerRanker::DetermineValueAmount(Value value) {
	int valueCounter = 0;
	for (int c = 0; c < this->hand.cards.size(); c++) {
		if (this->hand.cards.at(c).card_value == value)
			valueCounter++;
	}
	return valueCounter;
}