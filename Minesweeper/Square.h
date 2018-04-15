#pragma once

#include <SFML\Graphics.hpp>

enum eStatus { unrevealed, revealed, flagged, questioned };

class cSquare
{
	static sf::Font _font;

	eStatus _status;
	sf::RectangleShape _square;
	sf::Text _bombsNumber;
	bool _bomb;

	static bool init();

	void setBombsNumber(unsigned short bombsAround);
	void refreshStatus(unsigned short bombsAround);

public:

	cSquare() {};
	cSquare(unsigned short x, unsigned short y, sf::Vector2f startPos, unsigned short size);

	void click(unsigned short bombsAround);

	bool getBomb();
	void setBomb();
	sf::RectangleShape getRect();
	eStatus getStatus();

	void display(sf::RenderWindow &win);
};