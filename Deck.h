#pragma once
#include "Card.h"
#include <stdlib.h>
#include <time.h>

class Deck : public Card {
public:
	Deck();
	~Deck();
	Card Draw();
	void Shuffle();
	void loadCards();
	Card getCard(); 
	void Discard(Card playerCard);
public:
	Card* deck_of_cards;
	int size;
	int top;
};
