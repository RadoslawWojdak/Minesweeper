#include "Square.h"

void cSquare::setBombsNumber(unsigned short bombsAround)
{
	_bombsNumber.setString(bombsAround);
}

void cSquare::refreshStatus(unsigned short bombsAround)
{
	switch (_status)
	{
	case unrevealed:
		_square.setFillColor(sf::Color(255, 255, 255));
		break;
	case revealed:
	{
		if (_bomb)
			_square.setFillColor(sf::Color(0, 0, 0));
		else if (!bombsAround)
			_square.setFillColor(sf::Color(192, 192, 192));
		else
		{
			_square.setFillColor(sf::Color(224, 224, 224));
			setBombsNumber(bombsAround);
		}
		break;
	}
	case flagged:
		_square.setFillColor(sf::Color(48, 48, 224));
		break;
	case questioned:
		_square.setFillColor(sf::Color(48, 224, 48));
		break;
	}
}

cSquare::cSquare(unsigned short x, unsigned short y, sf::Vector2f startPos, unsigned short size)
{
	double thick = 1.0f;
	if (size < 8)
		thick = 0.5f;

	_square.setSize(sf::Vector2f(size - thick * 2, size - thick * 2));
	_square.setOutlineThickness(thick);
	_square.setOutlineColor(sf::Color(128, 128, 128));
	_square.setOrigin(size / 2, size / 2);

	_square.setPosition
	(
		startPos.x + thick + _square.getOrigin().x + x * size,
		startPos.y + thick + _square.getOrigin().y + y * size
	);

	_status = unrevealed;
	_bomb = false;

	_bombsNumber = cText(_square.getPosition(), "", (int)size * 0.8f, sf::Color::Black);
}

void cSquare::click(unsigned short bombsAround, sf::Mouse::Button buttonReleased)
{
	if (buttonReleased == sf::Mouse::Button::Left)
	{
		if (_status != flagged)
			_status = revealed;
	}
	else if (buttonReleased == sf::Mouse::Button::Right)
	{
		if (_status != revealed)
		{
			if (_status == flagged)
				_status = unrevealed;
			else
				_status = flagged;
		}
	}
	else if (buttonReleased == sf::Mouse::Button::Middle)
	{
		if (_status != revealed && _status != flagged)
		{
			if (_status == questioned)
				_status = unrevealed;
			else
				_status = questioned;
		}
	}

	refreshStatus(bombsAround);
}

bool cSquare::getBomb()
{
	return _bomb;
}

void cSquare::setBomb()
{
	_bomb = true;
}

sf::Vector2f cSquare::getSize()
{
	sf::Vector2f size;
	size.x = _square.getSize().x + _square.getOutlineThickness() * 2;
	size.y = _square.getSize().y + _square.getOutlineThickness() * 2;
	
	return size;
}

sf::RectangleShape cSquare::getRect()
{
	return _square;
}

eStatus cSquare::getStatus()
{
	return _status;
}

void cSquare::display(sf::RenderWindow &win, bool gameOver)
{
	if (_status == unrevealed || _status == questioned)
	{
		if (getRect().getGlobalBounds().contains(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y) && !gameOver)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				_square.setFillColor(sf::Color(196, 196, 196));
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
				_square.setFillColor(sf::Color(96, 224, 96));
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				_square.setFillColor(sf::Color(96, 96, 224));
		}
		else
			refreshStatus(0);
	}

	win.draw(_square);
	win.draw(_bombsNumber);
}