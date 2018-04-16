#include "RestartButton.h"

cRestartButton::cRestartButton(sf::Vector2f pos, unsigned short size)
{
	_rect.setOrigin(size / 2, size / 2);
	_rect.setSize(sf::Vector2f(size, size));
	_rect.setPosition(pos.x, pos.y);
	_rect.setOutlineThickness(1.0f);
	_rect.setOutlineColor(sf::Color::Black);
	_rect.setFillColor(sf::Color::White);

	_text = cText(pos, "R", 24, sf::Color(64, 64, 64));
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