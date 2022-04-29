#pragma once
#include "Hand.h"

class Player : public Hand {
public:
	Player();
	~Player();
	Card chooseCard(Card lastCard, int playerNum);
	Color chooseColor(int playerNum);
	void deleteCard(Card newCard);
	void addCard(Card newCard);
	int getCardCount();
	Card DisplayCards(Card lastCard);
public:
	Hand* pHand;
};