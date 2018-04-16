#include "Text.h"
#include <iostream>

sf::Font cText::_defaultFont;

cText::cText(sf::Vector2f pos, const sf::String &text, unsigned int charSize, sf::Color col)
{
	this->setCharacterSize(charSize);
	this->setFillColor(col);
	this->setFont(_defaultFont);
	this->setPosition(pos);
	this->setString(text);

	this->setOriginInCenter();
}

bool cText::init()
{
	if (!_defaultFont.loadFromFile("font.ttf"))
	{
#ifdef _DEBUG
		std::cerr << "ERROR: File \"font.ttf\" not found!\n";
#endif
		return false;
	}
	return true;
}

void cText::setOriginInCenter()
{
	sf::FloatRect textRect = getLocalBounds();
	this->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void cText::setString(int number)
{
	char buffer[10];
	_itoa_s(number, buffer, 10, 10);
	setString(buffer);
	this->setOriginInCenter();
}

void cText::setString(const sf::String &string)
{
	Text::setString(string);
	this->setOriginInCenter();
}