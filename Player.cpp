#include "Player.h"


Player::Player() {
	pHand = new Hand;
}

Player::~Player() {}

//adds a card to the hand
void Player::addCard(Card newCard) {
	pHand->addCard(newCard);
}

//deletes a card from the hand
void Player::deleteCard(Card newCard) {
	pHand->deleteCard(newCard);
}

//Returns the number of cards in the hand
int Player::getCardCount() {
	return pHand->getCardCount();
}

//If there is a card to be played, the card is returned.
Card Player::chooseCard(Card lastCard, int playerNum) {
	for (int i = 0; i < 108; i++) {
		if ((pHand->getCardInfo(i).cardColor == lastCard.cardColor || pHand->getCardInfo(i).cardNumber == lastCard.cardNumber || pHand->getCardInfo(i).cardColor == Color::Wild) && (pHand->getCardInfo(i).cardColor != Color::Removed)) {
			if (playerNum == 0) {
				Card temp = this->DisplayCards(lastCard);
				if (temp.cardColor != Color::Removed)
					return temp;
				else 
					return(pHand->getCardInfo(i));
			}
			else
				return(pHand->getCardInfo(i));
		}
	}
	Card draw;
	draw.cardColor = Color::Removed;
	draw.cardNumber = -1;
	return(draw);
}

//Returns a color that is paired with a wild card
Color Player::chooseColor(int playerNum) {
	int color;
	if (playerNum == 0) {
		std::cout << "Select a card color\n\n";
		std::cout << "[1] Blue\n";
		std::cout << "[2] Red\n";
		std::cout << "[3] Green\n";
		std::cout << "[4] Yellow\nColor: ";
		std::cin >> color;
		system("cls");
	}
	else {
		srand(time(NULL));
		color = rand() % 4 + 1;
	}
	if (color == 1)
		return Color::Blue;
	else if (color == 2)
		return Color::Red;
	else if (color == 3)
		return Color::Green;
	else
		return Color::Yellow;
}

//Displays the avaliable cards that can be discarded. Returns the card
Card Player::DisplayCards(Card lastCard) {
	for (int i = 0; i < 108; i++) {
		if (pHand->getCardInfo(i).cardColor != Color::Removed && (pHand->getCardInfo(i).cardColor == lastCard.cardColor || pHand->getCardInfo(i).cardNumber == lastCard.cardNumber)) {
			Color color = pHand->getCardInfo(i).cardColor;
			std::string cardColor;
			switch (color)
			{
			case Color::Red:
				cardColor = "Red";
				break;
			case Color::Green:
				cardColor = "Green";
				break;
			case Color::Blue:
				cardColor = "Blue";
				break;
			case Color::Yellow:
				cardColor = "Yellow";
				break;
			}
			if (pHand->getCardInfo(i).cardNumber == 10)
				std::cout << "[" << i << "] Skip" << " " << cardColor << "\n";
			else if (pHand->getCardInfo(i).cardNumber == 11)
				std::cout << "[" << i << "] Draw two" << " " << cardColor << "\n";
			else if (pHand->getCardInfo(i).cardNumber == 12)
				std::cout << "[" << i << "] Reverse" << " " << cardColor << "\n";
			else if (pHand->getCardInfo(i).cardNumber == 13)
				std::cout << "[" << i << "] Wild\n";
			else if (pHand->getCardInfo(i).cardNumber == 14)
				std::cout << "[" << i << "] +4 Wild\n";
			else {
				std::cout << "[" << i << "] " << pHand->getCardInfo(i).cardNumber << " " << cardColor << "\n";
			}
		}
	}
	int card;
	std::cin >> card;
	system("cls");
	return pHand->getCardInfo(card);
}
