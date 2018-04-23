#include "Button.h"

cButton::cButton(const sf::String &text, const sf::Vector2f &pos, const sf::Vector2f &size)
{
	_rect.setSize(size);
	_rect.setOrigin((int)_rect.getGlobalBounds().width / 2, (int)_rect.getGlobalBounds().height / 2);
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::White);
	_rect.setOutlineThickness(1);
	_rect.setOutlineColor(sf::Color::Black);

	_text = cText(pos, text, (int)(size.y * 0.75f));
}

bool cButton::isMouseOn(const sf::RenderWindow &win)
{
	return _rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win)));
}

bool cButton::isClicked(const sf::RenderWindow &win)
{
	if (isMouseOn(win) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return true;
	return false;
}

void cButton::setColor(const sf::Color &buttonColor, const sf::Color &textColor)
{
	_rect.setFillColor(buttonColor);
	_text.setFillColor(textColor);
}

void cButton::autoColor(sf::RenderWindow &win)
{
	if (isClicked(win))
	{
		_rect.setFillColor(sf::Color(128, 128, 128));
		_text.setFillColor(sf::Color::Black);
	}
	else if (isMouseOn(win))
	{
		_rect.setFillColor(sf::Color(228, 228, 228));
		_text.setFillColor(sf::Color(48, 48, 48));
	}
	else
	{
		_rect.setFillColor(sf::Color::White);
		_text.setFillColor(sf::Color(64, 64, 64));
	}
}

void cButton::display(sf::RenderWindow &win, bool adjustColor)
{
	if (adjustColor)
		autoColor(win);
	win.draw(_rect);
	win.draw(_text);
}

sf::String cButton::getString()
{
	return _text.getString();
}

void cButton::setString(sf::String str)
{
	_text.setString(str);
}