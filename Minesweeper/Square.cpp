#include "Square.h"

cSquare::cSquare(unsigned short x, unsigned short y)
{
	const sf::Vector2f START_DRAW_POS = sf::Vector2f(0, 0);
	const int SIZE = 16;
	
	this->setSize(sf::Vector2f(SIZE, SIZE));
	this->setOutlineThickness(1.0f);
	this->setOutlineColor(sf::Color(128, 128, 128));
	this->setOrigin(SIZE / 2, SIZE / 2);

	int thick = getOutlineThickness();
	this->setPosition
	(
		START_DRAW_POS.x + thick + getOrigin().x + x * (SIZE + thick * 2),
		START_DRAW_POS.y + thick + getOrigin().y + y * (SIZE + thick * 2)
	);

	_status = unrevealed;
}