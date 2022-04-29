#pragma once
#include "Deck.h"

class Hand {
public:
	Hand();
	~Hand();
	void deleteCard(Card discard);
	void addCard(Card newCard);
	int getCardCount();
	Card getCardInfo(int cardNum);
	void setCardCount();
private:
	int count;
	Card* cards;
};