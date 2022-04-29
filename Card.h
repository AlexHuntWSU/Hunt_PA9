#pragma once
#include <iostream>
#include <string>

enum class Color{Red, Blue, Green, Yellow, Wild, Removed};

class Card {
public:
	Card();
	void setColor(Color newColor);
	int cardNumber;
	Color cardColor;
};
