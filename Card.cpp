#include "Card.h"

//Removed and -1 are considered empty cards in all the functions
Card::Card() {
	cardColor = Color::Removed;
	cardNumber = -1;
}

//Sets the color of the card - used for declaring a wild card
void Card::setColor(Color newColor) {
	this->cardColor = newColor;
}