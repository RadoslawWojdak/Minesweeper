#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"

class cRestartButton
{
	sf::RectangleShape _rect;
	cText _text;

public:
	cRestartButton(sf::Vector2f pos, unsigned short size);
	
	bool click(sf::RenderWindow &win, sf::Mouse::Button button);

	void display(sf::RenderWindow &win);
};