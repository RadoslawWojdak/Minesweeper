#include "RestartButton.h"

cRestartButton::cRestartButton(sf::Vector2f pos, unsigned short size)
	: cButton("R", pos, sf::Vector2f(size, size))
{
	;
}

void cRestartButton::display(sf::RenderWindow &win)
{
	autoColor(win);
	cButton::display(win);
}