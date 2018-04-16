#pragma once

#include <SFML\Graphics.hpp>

class cRestartButton
{
	static sf::Font _font;

	sf::RectangleShape _rect;
	sf::Text _text;

	bool init();

public:
	cRestartButton(sf::Vector2i pos, unsigned short size);
	
	bool click(sf::RenderWindow &win, sf::Mouse::Button button);

	void display(sf::RenderWindow &win);
};