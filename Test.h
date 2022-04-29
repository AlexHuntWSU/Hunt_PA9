#include "Player.h"

class Test {
public:
	void setCardCount(Player* players, Deck& main, int cards);
	void declareWinner(Player* players);
	void emptyDeck(Deck& main, Player* players, int cards);
	void cardNumbers(sf::RenderWindow& window, sf::Font& font, Color color);
	void cardColors(sf::RenderWindow& window, sf::Font& font, int number);
};

//Sets initial card count
void Test::setCardCount(Player* players, Deck& main, int cards) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < cards; j++) {
			players[i].addCard(main.Draw());
		}
	}
}

//Sets the card count of the player to 0 - declaring a winner
void Test::declareWinner(Player* players) {
	players->pHand->setCardCount();
}

//Displays one of each card number
void Test::cardNumbers(sf::RenderWindow& window, sf::Font& font, Color color) {
	cardFront card;
	for (int i = 1; i < 15; i++) {
		Card newCard;
		newCard.cardNumber = i;
		newCard.setColor(color);
		card.setColor(newCard);
		card.setNumber(newCard, font);
		card.drawCard(window, sf::Vector2f(750, 500));
		window.display();
		system("pause");
	}
}

//Displays one of each card color
void Test::cardColors(sf::RenderWindow& window, sf::Font& font, int number) {
	cardFront card;
	for (int i = 0; i < 5; i++) {
		Card newCard;
		newCard.cardNumber = number;
		newCard.setColor((Color)i);
		card.setColor(newCard);
		card.setNumber(newCard, font);
		card.drawCard(window, sf::Vector2f(750, 500));
		window.display();
		system("pause");
	}
}

//Tests the end-game case of no cards to draw
void Test::emptyDeck(Deck& main, Player* players, int cards) {
	for (int i = 0; i < (108 - (cards * 4)); i++) {
		main.Draw();
	}
	this->setCardCount(players, main, cards);
}

