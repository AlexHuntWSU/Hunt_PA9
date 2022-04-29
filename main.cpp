#include <SFML/Graphics.hpp>
#include "Player.h"
#include "graphics.h"
#include "Test.h"

//gets the next player based on the direction of play
int nextPlayer(int playerNum, int direction) {
	if (direction == 1) {
		if (playerNum == 3) {
			return 0;
		}
		else
			return playerNum + 1;
	}
	else {
		if (playerNum < 0) {
			return 3;
		}
		else
			return playerNum - 1;
	}
}

//Returns if there are no more discards and draws avaliable
int noDraw(Deck& main, Player* players, Card last, int current, int direction) {
	int game = 0;
	int num = nextPlayer(current, direction);
	if (main.top < 0) {
		if (players[num].chooseCard(last, num).cardColor != Color::Removed) {
			game = 1;
		}
		else {
			num++;
			noDraw(main, players, last, num, direction);
		}
	}
	else {
		game = 1;
	}
	return game;
}

//Displays the number and color of a card
void displayDiscard(Card discard) {
	Color color = discard.cardColor;
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
	if (discard.cardNumber == 10)
		std::cout << "Skip" << " " << cardColor << "\n";
	else if (discard.cardNumber == 11)
		std::cout << "Draw two" << " " << cardColor << "\n";
	else if (discard.cardNumber == 12)
		std::cout << "Reverse" << " " << cardColor << "\n";
	else if (discard.cardNumber == 13)
		std::cout << "Wild " << cardColor << "\n";
	else if (discard.cardNumber == 14)
		std::cout << "+4 Wild " << cardColor << "\n";
	else {
		std::cout << discard.cardNumber << " " << cardColor << "\n";
	}
}

//Returns the discard for the current player
Card getPlayerDiscard(Deck* main, Player* players, Deck* discard, int playerNum, sf::RenderWindow& window, sf::Font& font) {
	cardFront* front = new cardFront;
	if (discard->getCard().cardNumber == 14) {//+4 - adds 4 cards
		for (int i = 0; i < 4; i++) {
			std::cout << "Player " << playerNum + 1 << " draws ";
			displayDiscard(main->getCard());
			players->addCard(main->Draw());
		}
	}
	if (discard->getCard().cardNumber == 11) {//+2 - adds 2 cards
		for (int i = 0; i < 2; i++) {
			std::cout << "Player " << playerNum + 1 << " draws ";
			displayDiscard(main->getCard());
			players->addCard(main->Draw());
		}
	}
	Card cardCheck = players->chooseCard(discard->getCard(), playerNum); //gets card from player
	if (cardCheck.cardColor == Color::Removed) { //No avaliable cards - draw another and run the function again
		std::cout << "Player " << playerNum + 1 << " draws ";
		displayDiscard(main->getCard());
		players->addCard(main->Draw());
		getPlayerDiscard(main, players, discard, playerNum, window, font);
	}
	else { 
		players->deleteCard(cardCheck); //Deleted the card if it can be discarded
		if (cardCheck.cardColor == Color::Wild) {
			cardCheck.setColor(players->chooseColor(playerNum)); //Gets the new color if card is a wild
		}

		std::cout << "Player " << playerNum + 1 << " discards ";
		displayDiscard(cardCheck);
	
		return cardCheck; //Returns the card to be added to the discard pile
	}
}

//Draws the back of cards onto the screen
void displayCards(sf::RenderWindow& window) {
	cardBack back;
	back.setColor();
	back.drawCard(window, sf::Vector2f(250, 500));
	back.drawCard(window, sf::Vector2f(150, 500));
	back.drawCard(window, sf::Vector2f(200, 500));
	back.drawCard(window, sf::Vector2f(1550, 500));
	back.drawCard(window, sf::Vector2f(1450, 500));
	back.drawCard(window, sf::Vector2f(1500, 500));
	back.drawCard(window, sf::Vector2f(850, 100));
	back.drawCard(window, sf::Vector2f(750, 100));
	back.drawCard(window, sf::Vector2f(800, 100));
	back.drawCard(window, sf::Vector2f(950, 500));
}

int main() {

	sf::Font font;
	//Loads the font for card number
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "error";
	}
	Deck main;
	Deck discard;
	Player players[4];
	Test t;

	sf::RenderWindow window(sf::VideoMode(1900, 1400), "PA9 - UNO");
	window.clear(sf::Color(54, 203, 119, 1));
	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed()) {
				window.close();
			}
			main.loadCards();
			cardFront front; //discard pile graphic

			do {
				if (main.getCard().cardColor == Color::Wild) {
					main.Shuffle();
				}
				else {
					front.setNumber(main.getCard(), font);
					front.setColor(main.getCard());
					discard.Discard(main.Draw()); //Adds first non wild-card to discard stack
				}
			} while (main.getCard().cardColor == Color::Wild);

			//Initial 7 card draw for all 4 players
			//for (int i = 0; i < 4; i++) {
			//	for (int j = 0; j < 7; j++) {
			//		players[i].addCard(main.Draw());
			//	}
			//}

			//Test case - 3 intitial cards
			t.setCardCount(players, main, 3); 
			//Tests the game over due to no cards - Helped identify an issue of not allowing discards after main has been emptied
			//t.emptyDeck(main, players, 3);


			displayCards(window);
			window.display();
			int currentPlayer = -1;
			int direction = 1; //Clockwise vs Counterclockwise
			bool win = false;
			
			//Tests the display of card numbers
			//t.cardNumbers(window, font, Color::Blue);
			//Tests the display of card colors
			//t.cardColors(window, font, 14);

			while (win != true) {

				front.drawCard(window, sf::Vector2f(750, 500));
				window.display();
				if (discard.getCard().cardNumber == 10) { //skip
					currentPlayer = nextPlayer(currentPlayer, direction);
				}
				else if (discard.getCard().cardNumber == 12) { //reverse
					if (direction == 1)
						direction = -1;
					else
						direction = 1;
				}
				currentPlayer = nextPlayer(currentPlayer, direction);
				std::cout << "Player: " << (currentPlayer + 1) << " - " << "Cards: " << players[currentPlayer].getCardCount() << std::endl;
				Card c1 = getPlayerDiscard(&main, &players[currentPlayer], &discard, currentPlayer, window, font);
				discard.Discard(c1);
				front.setColor(c1); //updates the new discard info
				front.setNumber(c1, font);
				
				system("pause");
				system("cls");

				//declareWinner(&players[currentPlayer]); //Tests if the cardcount = 0 is picked up as a winner
				if (players[currentPlayer].getCardCount() == 0) {
					win = true;
					std::cout << "Player " << (currentPlayer + 1) << " Wins" << std::endl;
					system("pause");
					window.close();
				}
				else if (noDraw(main, players, c1, currentPlayer, direction) == 0) { //Deck of cards run out
					win = true;
					std::cout << "Restart game, no winners" << std::endl;
					system("pause");
					window.close();

				}
			}
		}
	}

	return 0;
}