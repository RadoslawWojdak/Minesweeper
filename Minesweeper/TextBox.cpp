#include "TextBox.h"

cTextBox::cTextBox(const sf::Vector2f &pos, const sf::Vector2f &size, bool onlyDigits, unsigned short maxChars)
{
	_rect.setSize(size);
	_rect.setOrigin((int)_rect.getGlobalBounds().width / 2, (int)_rect.getGlobalBounds().height / 2);
	_rect.setPosition(pos);
	_rect.setFillColor(sf::Color::White);
	_rect.setOutlineThickness(1);
	_rect.setOutlineColor(sf::Color::Black);

	_text = cText(pos, "", (int)(size.y * 0.75f));
	
	if (maxChars < 256)
		_maxChars = maxChars;
	_onlyDigits = onlyDigits;
}

void cTextBox::putSign(const sf::Keyboard::Key &key)
{
	if (_text.getString().getSize() > 0 && key == sf::Keyboard::BackSpace)
	{
		sf::String temp = _text.getString();
		temp.erase(temp.getSize() - 1, 1);
		_text.setString(temp);
	}
	else if (_text.getString().getSize() < _maxChars)
	{
		if (_onlyDigits)
		{
			char character = cTextActions::keyToDigitChar(key);
			if (character != -1)
				_text.setString(_text.getString() + character);
		}
		else
		{
			char character = cTextActions::keyToDigitChar(key);
			if (character != -1)
				_text.setString(_text.getString() + character);
		}
	}
}

bool cTextBox::isMouseOn(sf::RenderWindow &win)
{
	return _rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win)));
}

cText cTextBox::getText()
{
	return _text;
}

void cTextBox::display(sf::RenderWindow &win)
{
	win.draw(_rect);
	win.draw(_text);
}