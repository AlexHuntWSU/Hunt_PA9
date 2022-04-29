#include <SFML/Graphics.hpp>
#include <string>

class cardBase {
public:
	cardBase() {
		card.setSize(sf::Vector2f(120, 180));
		center.setRadius(61);
		number.setString("");
	}
	void drawCard(sf::RenderWindow& window, const sf::Vector2f& pos);
	void setColor(sf::Color color);
	void setNumber(sf::String string, sf::Font& font, sf::RenderWindow& window);
protected:
	sf::RectangleShape card;
	sf::CircleShape center;
	sf::Text number;
};

//Base class - sets card color
void cardBase::setColor(sf::Color color) {
	card.setFillColor(color);
	center.setFillColor(color);
}

//Base class - draws the card - used with the derived front and back classes
void cardBase::drawCard(sf::RenderWindow& window, const sf::Vector2f& pos) {
	card.setPosition(pos);
	card.setOutlineThickness(3);
	card.setOutlineColor(sf::Color::White);
	center.setPosition(card.getPosition().x - 0.8, card.getPosition().y + 30);
	number.setPosition(card.getPosition().x - 0.8, card.getPosition().y + 30);
	window.draw(card);
	window.draw(center);
	window.draw(number);
}

class cardBack : public cardBase{
public:
	void setColor();
	void setNumber(sf::String number1, sf::Font& font, sf::RenderWindow& window);
private:
};

//Sets the color of back card to black and red
void cardBack::setColor() {
	card.setFillColor(sf::Color::Black);
	center.setFillColor(sf::Color::Red);
}

//Sets number of back card (card count)
void cardBack::setNumber(sf::String number1, sf::Font& font, sf::RenderWindow& window) {
	number.setString(number1);
	number.setCharacterSize(30);
	number.setFont(font);
	number.setPosition(card.getPosition().x - 750, card.getPosition().y + 500);
	number.setFillColor(sf::Color::Black);
	number.setStyle(sf::Text::Regular);
}

class cardFront : public cardBase {
public:
	void setColor(Card newCard);
	void setNumber(Card newCard, sf::Font& font);
private:
};

//Sets the color of the front card
void cardFront::setColor(Card newCard) {
	switch (newCard.cardColor) {
	case Color::Blue:
		card.setFillColor(sf::Color::Cyan);
		break;
	case Color::Red:
		card.setFillColor(sf::Color::Red);
		break;
	case Color::Green:
		card.setFillColor(sf::Color::Green);
		break;
	case Color::Yellow:
		card.setFillColor(sf::Color::Yellow);
		break;
	case Color::Wild:
		card.setFillColor(sf::Color::Black);
	}
}

//Sets the number of the front card
void cardFront::setNumber(Card newCard, sf::Font& font) {

	if (newCard.cardNumber == 10)
		number.setString("Skip");
	else if (newCard.cardNumber == 11)
		number.setString("+2");
	else if (newCard.cardNumber == 12)
		number.setString("Reverse");
	else if (newCard.cardNumber == 13)
		number.setString("Wild");
	else if (newCard.cardNumber == 14)
		number.setString("+4 Wild");
	else {
		std::string number1 = std::to_string(newCard.cardNumber);
		number.setString(number1);
	}
	number.setCharacterSize(30);
	number.setFont(font);
	number.setPosition(sf::Vector2f(550, 150));
	number.setFillColor(sf::Color::Black);
	number.setStyle(sf::Text::Regular);
}