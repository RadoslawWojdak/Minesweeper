#include "Square.h"

cSquare::cSquare(unsigned short x, unsigned short y)
{
	const sf::Vector2f START_DRAW_POS = sf::Vector2f(0, 0);
	const int SIZE = 16;
	
	this->setSize(sf::Vector2f(SIZE, SIZE));
	this->setOutlineThickness(1.0f);
	this->setOutlineColor(sf::Color(128, 128, 128));
	this->setOrigin(SIZE / 2, SIZE / 2);

	int thick = getOutlineThickness();
	this->setPosition
	(
		START_DRAW_POS.x + thick + getOrigin().x + x * (SIZE + thick * 2),
		START_DRAW_POS.y + thick + getOrigin().y + y * (SIZE + thick * 2)
	);

	_status = unrevealed;
	_bomb = false;
}

void cSquare::displayStatus()
{
	switch (_status)
	{
	case unrevealed:
		setFillColor(sf::Color(255, 255, 255));
		break;
	case revealed:
	{
		if (_bomb)
			setFillColor(sf::Color(0, 0, 0));
		else
			setFillColor(sf::Color(0, 0, 255));
		break;
	}
	case flagged:
		setFillColor(sf::Color(255, 0, 0));
		break;
	case questioned:
		setFillColor(sf::Color(0, 255, 0));
		break;
	}
}

void cSquare::click()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (_status != flagged)
			_status = revealed;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		if (_status != revealed)
		{
			if (_status == flagged)
				_status = unrevealed;
			else
				_status = flagged;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
		if (_status != revealed && _status != flagged)
		{
			if (_status == questioned)
				_status = unrevealed;
			else
				_status = questioned;
		}
	}

	displayStatus();
}

bool cSquare::getBomb()
{
	return _bomb;
}

void cSquare::setBomb()
{
	_bomb = true;
}