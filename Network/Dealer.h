#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Cards.h"
#include "Player.h"
#include <vector>
#pragma once

class Dealer{
  public:
    Dealer(int cardSize);
    void Shuffle();
    void DealCard(Player player);
    Hand cards;
  private:
    int cardSize;
    Hand Shuffle(Hand toShuffle);
    Hand GeneratePack();
};