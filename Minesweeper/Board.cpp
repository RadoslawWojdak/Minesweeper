#include "Board.h"

#include <ctime>
#include <iostream>

void Board::randBombs(unsigned short number)
{
	srand(time(NULL));

	for (unsigned short i = 0; i < number;)
	{
		int rnd = rand() % _size;
		if (!_square[rnd].getBomb())
		{
			_square[rnd].setBomb();
			++i;
		}
	}
}

Board::Board(unsigned short width, unsigned short height, unsigned short bombs)
{
	_size = width * height;
	_square = new cSquare[_size];

	cSquare* p = _square;
	for (unsigned short  i = 0; i < width; ++i)
	{
		for (unsigned short  j = 0; j < height; ++j)
			*p++ = cSquare(i, j);
	}

	if (width * height > bombs)
		randBombs(bombs);
	else	//Delete when the GUI is added
	{
#ifdef _DEBUG
		std::cerr << "ERROR: The number of bombs is greater than or equal to the size of the board!\n";
		system("PAUSE");
#endif
		delete[] _square;
		exit(1);
	}
}

Board::~Board()
{
	delete[] _square;
}

void Board::checkMouse(sf::RenderWindow &win)
{
	static bool click = true;
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!click)
		{
			click = true;
			for (cSquare* p = _square; p < _square + _size * sizeof(cSquare); p++)
			{
				if (p->getGlobalBounds().contains(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y))
				{
					p->click();
					break;
				}
			}
		}
	}
	else
		click = false;
}

void Board::display(sf::RenderWindow &win)
{
	cSquare* p = _square;
	for (int i = 0; i < _size; ++i)
		win.draw(*p++);
}