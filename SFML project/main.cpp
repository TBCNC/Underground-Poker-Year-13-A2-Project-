//#include "../Network/UserAccount.h"
#include <iostream>
#include "../Network/UserAccount.h"
#include "../Network/Server.h"
#include "../Network/PokerRanker.h"

int main() {
	//Server server("newServer", 666, false, "abc123");
	//server.Start();
	Hand hand;
	Card card1,card2,card3,card4,card5,card6,card7;
	card1.card_suit = Suit::CLUBS; card2.card_suit = Suit::CLUBS; card3.card_suit = Suit::CLUBS; card5.card_suit = Suit::CLUBS; card6.card_suit = Suit::CLUBS; card4.card_suit = Suit::DIAMONDS; card7.card_suit = Suit::DIAMONDS;
	card1.card_value = Value::TWO; card2.card_value = Value::THREE; card3.card_value = Value::FOUR; card5.card_value = Value::FIVE; card6.card_value = Value::SIX; card4.card_value = Value::QUEEN; card7.card_value = Value::NINE;
	hand.cards = { card1,card2,card3,card4,card5,card6,card7 };
	PokerRanker ranker(hand);
	std::cout << ranker.RankHand() << std::endl;
	system("pause");
}
