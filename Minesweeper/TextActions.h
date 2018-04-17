#pragma once

#include <SFML\Graphics.hpp>

class cTextActions
{
	cTextActions() {};

public:
	static char keyToDigitChar(sf::Keyboard::Key key);
	static char keyToChar(sf::Keyboard::Key key);
	static sf::String keyToString(sf::Keyboard::Key key);
};