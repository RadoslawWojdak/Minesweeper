#pragma once

#include <SFML\Graphics.hpp>

class cSquare :public sf::RectangleShape
{
	enum eStatus { unrevealed, revealed, flagged, questioned } _status;
	bool _bomb;

	void displayStatus();

public:
	cSquare(unsigned short x, unsigned short y);

	void click();
};