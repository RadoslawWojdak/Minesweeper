#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"

enum eStatus { unrevealed, revealed, flagged, questioned };

class cSquare
{
	eStatus _status;
	sf::RectangleShape _square;
	cText _bombsNumber;
	bool _bomb;

	void setBombsNumber(unsigned short bombsAround);
	void refreshStatus(unsigned short bombsAround);

public:

	cSquare() {};
	cSquare(unsigned short x, unsigned short y, sf::Vector2f startPos, unsigned short size);

	void click(unsigned short bombsAround, sf::Mouse::Button buttonReleased);

	bool getBomb();
	void setBomb();
	sf::RectangleShape getRect();
	eStatus getStatus();

	void display(sf::RenderWindow &win, bool gameOver);
};