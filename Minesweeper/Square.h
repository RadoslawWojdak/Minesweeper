#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"
#include "Board.h"

enum eStatus { unrevealed, revealed, flagged, questioned };

class cBoard;

class cSquare
{
	eStatus _status;
	sf::RectangleShape _square;
	cText _bombsNumber;
	bool _bomb;

	void setBombsNumber(unsigned short bombsAround);
	void refreshStatus(unsigned short bombsAround);

	void onMouse(sf::RenderWindow &win, bool isGameOver);
	void outMouse(sf::RenderWindow &win);

public:

	cSquare() {};
	cSquare(unsigned short x, unsigned short y, sf::Vector2f startPos, unsigned short size);

	void click(unsigned short bombsAround, sf::Mouse::Button buttonReleased);

	bool getBomb();
	void setBomb();
	short getBombNumber();
	sf::Vector2f getSize();
	sf::RectangleShape getRect();
	eStatus getStatus();
	void setColor(const sf::Color &col);

	void display(sf::RenderWindow &win);

	friend cBoard;
};