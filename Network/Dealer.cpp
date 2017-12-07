#include "Dealer.h"

Dealer::Dealer(int cardSize){
  this->cardSize=cardSize;
  this->cards = GeneratePack();
}
bool Exists(std::vector<Card> deck, Card card){
  for(int c=0;c<deck.size();c++){
    if(deck.at(c).card_suit==card.card_suit && deck.at(c).card_value==card.card_value){
      return true;
    }
  }
  return false;
}
void Dealer::DealCard(Player player){
  player.hand.cards.push_back(this->cards.cards.at(0));
  //this->cards.cards.erase(std::remove(this->cards.cards.begin(), this->cards.cards.end(), 0), this->cards.cards.end());
}
Hand Dealer::GeneratePack(){
  Hand deck;
  int roundCounter=1;
  for(int i=0; i<4;i++){
    for(int c=1; c<=(int)cardSize/4;c++){
      Card newCard;
      newCard.card_suit=(Suit)i;
      newCard.card_value=(Value)c;
      deck.cards.push_back(newCard);
    }
  }
  deck=this->Shuffle(deck);
  return deck;
}
Hand Dealer::Shuffle(Hand toShuffle){
  srand(unsigned(std::time(0)));
  for(int k=0;k<(rand()%30)+10;k++){
    std::random_shuffle(toShuffle.cards.begin(),toShuffle.cards.end());
  }
  return toShuffle;
}
void Dealer::Shuffle(){
  this->cards = this->Shuffle(this->cards);
}