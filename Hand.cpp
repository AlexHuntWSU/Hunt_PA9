#include "Hand.h"

Hand::Hand() {
	count = 0;
	cards = new Card[108];
}

Hand::~Hand() {}

//Deletes card by setting the color to removed and number to -1.
void Hand::deleteCard(Card discard) {
	for (int i = 0; i < 108; i++) {
		if (cards[i].cardColor == discard.cardColor && cards[i].cardNumber == discard.cardNumber) {
			cards[i].cardColor = Color::Removed;
			cards[i].cardNumber = -1;
			count--;
			break;
		}	
	}
}

//Returns the card info based on card index
Card Hand::getCardInfo(int cardNum) {
	return cards[cardNum];
}

//Adds a card to the hand in the first avaliable slot
void Hand::addCard(Card newCard) {
	for (int i = 0; i < 108; i++) {
		if (cards[i].cardColor == Color::Removed && cards[i].cardNumber == -1) {
			cards[i].cardColor = newCard.cardColor;
			cards[i].cardNumber = newCard.cardNumber;
			count++;
			break;
		}
	}
}

//Returns the card count
int Hand::getCardCount() {
	return count;
}

//For testing a win
void Hand::setCardCount() {
	this->count = 0;
}