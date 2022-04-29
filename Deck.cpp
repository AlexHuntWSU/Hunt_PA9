#include "Deck.h"

//Creates a new deck of 108 cards
Deck::Deck() {
	deck_of_cards = new Card[108];
	size = 0;
	top = -1;
}

Deck::~Deck() {}

//returns the card at the top of the array. sets the top to -1 to make sure the card can't be drawn again
Card Deck::Draw() {
	Card topCard = deck_of_cards[top];
	if (top > -1) {
		top--;
		return topCard;
	}
}

//Adds a card to the array and sets its index to the top
void Deck::Discard(Card playerCard) {
	if (top < 107){
		top++;
		deck_of_cards[top] = playerCard;
	}
}

//Shuffles the deck of cards by randomly assigning indexes
void Deck::Shuffle() {
	srand(time(NULL));
	for (int i = 107; i > 0; i--) {
		int j = rand() % (i + 1);
		Card temp = deck_of_cards[i];
		deck_of_cards[i] = deck_of_cards[j];
		deck_of_cards[j] = temp;
	}
}

//sets the colors and numbers of the 108 cards in the deck
void Deck::loadCards() {
	int i = 0, j = 0, k = 0;
	for (j = 0; j < 4; j++) {
		deck_of_cards[size].cardColor = (Color)j;
		deck_of_cards[size].cardNumber = i;
		top++;
		size++;
	}
	for (k = 0; k < 2; k++) {
		for (i = 1; i < 13; i++) {
			for (j = 0; j < 4; j++) {
				deck_of_cards[size].cardColor = (Color)j;
				deck_of_cards[size].cardNumber = i;
				top++;
				size++;
			}
		}
	}
	for (i = 13; i < 15; i++) {//wild, +4 wild
		for (j = 0; j < 4; j++) {
			deck_of_cards[size].cardColor = Color::Wild;
			deck_of_cards[size].cardNumber = i;
			top++;
			size++;
		}
	}
	this->Shuffle();
}

//Returns the card information at the top of the array
Card Deck::getCard() {
	return deck_of_cards[top];
}