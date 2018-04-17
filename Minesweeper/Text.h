#pragma once

#include <SFML\Graphics.hpp>

class cText :public sf::Text
{
	static sf::Font _defaultFont;
	void setOriginInCenter();

public:
	cText(sf::Vector2f pos = { 0,0 }, const sf::String &text = "", unsigned int charSize = 12, sf::Color col = sf::Color::Black);
	
	static bool init();

	void setString(int number);
	void setString(const sf::String &string);
	int getNumber();
};