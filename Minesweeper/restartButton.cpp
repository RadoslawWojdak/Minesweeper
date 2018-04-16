#include "RestartButton.h"

#include <iostream>

sf::Font cRestartButton::_font;

bool cRestartButton::init()
{
	if (!_font.loadFromFile("font.ttf"))
	{
#ifdef _DEBUG
		std::cerr << "ERROR: File \"arial.ttf\" not found!\n";
#endif
		return false;
	}

	return true;
}

cRestartButton::cRestartButton(sf::Vector2i pos, unsigned short size)
{
	_rect.setOrigin(size / 2, size / 2);
	_rect.setSize(sf::Vector2f(size, size));
	_rect.setPosition(pos.x, pos.y);
	_rect.setOutlineThickness(1.0f);
	_rect.setOutlineColor(sf::Color::Black);
	_rect.setFillColor(sf::Color::White);

	static bool init = false;
	if (!init)
	{
		init = true;
		if (!cRestartButton::init())
		{
#ifdef _DEBUG
			std::cerr << "ERROR: \"Restart Button\" init error!\n";
			system("PAUSE");
#endif
			exit(4);
		}
	}
	_text.setFont(_font);
	_text.setFillColor(sf::Color(64, 64, 64));
	_text.setCharacterSize(size / 1.5f);
	_text.setString("R");
	_text.setOrigin((int)_text.getGlobalBounds().width / 2, (int)(_text.getGlobalBounds().height * 0.75f));
	_text.setPosition(pos.x, pos.y);
}

bool cRestartButton::click(sf::RenderWindow &win, sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left && _rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win))))
		return true;
	return false;
}

void cRestartButton::display(sf::RenderWindow &win)
{
	if (_rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			_rect.setFillColor(sf::Color(128, 128, 128));
			_text.setFillColor(sf::Color::Black);
		}
		else
		{
			_rect.setFillColor(sf::Color(228, 228, 228));
			_text.setFillColor(sf::Color(48, 48, 48));
		}
	}
	else
	{
		_rect.setFillColor(sf::Color::White);
		_text.setFillColor(sf::Color(64, 64, 64));
	}

	win.draw(_rect);
	win.draw(_text);
}