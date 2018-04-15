#pragma once

#include <SFML\Graphics.hpp>

class cSquare
{
	static sf::Font _font;

	enum eStatus { unrevealed, revealed, flagged, questioned } _status;
	sf::RectangleShape _square;
	sf::Text _bombsNumber;
	bool _bomb;

	static bool init();

	void setBombsNumber(unsigned short bombsAround);
	void refreshStatus(unsigned short bombsAround);

public:

	cSquare() {};
	cSquare(unsigned short x, unsigned short y);

	void click(unsigned short bombsAround);

	bool getBomb();
	void setBomb();
	sf::RectangleShape getRect();

	void display(sf::RenderWindow &win);
};