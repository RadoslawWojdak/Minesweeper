#pragma once

#include <SFML\Graphics.hpp>
#include "TextActions.h"
#include "Text.h"

class cTextBox
{
	sf::RectangleShape _rect;
	cText _text;
	unsigned int _maxChars;
	bool _onlyDigits;

public:
	cTextBox(const sf::Vector2f &pos = { 0,0 }, const sf::Vector2f &size = { 64,24 }, bool onlyDigits = false, unsigned short maxChars = 256);
	
	void putSign(const sf::Keyboard::Key &key);
	void setString(const sf::String &string);
	sf::Color getTextColor();
	void setTextColor(const sf::Color &col);

	bool isMouseOn(sf::RenderWindow &win);

	cText getText();
	
	void display(sf::RenderWindow &win);
};