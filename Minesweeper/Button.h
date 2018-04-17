#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"

class cButton
{
	sf::RectangleShape _rect;
	cText _text;

public:
	cButton(const sf::String &text = "", const sf::Vector2f &pos = { 0,0 }, const sf::Vector2f &size = { 64,24 });

	bool isMouseOn(const sf::RenderWindow &win);
	bool isClicked(const sf::RenderWindow &win);

	void setColor(const sf::Color &buttonColor, const sf::Color &textColor = sf::Color::Black);
	void autoColor(sf::RenderWindow &win);

	void display(sf::RenderWindow &win);
};