#include "Board.h"

#include <ctime>
#include <iostream>

void cBoard::randBombs(unsigned short number)
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

unsigned short cBoard::countBombsAround(unsigned short x, unsigned short y)
{
	int sum = 0;

	if (x > 0)
	{
		if (y > 0)
			sum += _square[(x - 1) * _height + y - 1].getBomb();
		sum += _square[(x - 1) * _height + y].getBomb();
		if (y < _height)
			sum += _square[(x - 1) * _height + y + 1].getBomb();
	}

	if (y > 0)
		sum += _square[x * _height + y - 1].getBomb();
	if (y < _height)
		sum += _square[x * _height + y + 1].getBomb();

	if (x < _width)
	{
		if (y > 0)
			sum += _square[(x + 1) * _height + y - 1].getBomb();
		sum += _square[(x + 1) * _height + y].getBomb();
		if (y < _height)
			sum += _square[(x + 1) * _height + y + 1].getBomb();
	}

	return sum;
}

cBoard::cBoard(unsigned short width, unsigned short height, unsigned short bombs)
{
	_width = width;
	_height = height;
	_size = width * height;
	_square = new cSquare[_size];

	cSquare* p = _square;
	for (unsigned short  i = 0; i < height; ++i)
	{
		for (unsigned short  j = 0; j < width; ++j)
			*p++ = cSquare(i, j);
	}

	if (width * height > bombs)
		randBombs(bombs);
	else	//Delete when the GUI is added
	{
#ifdef _DEBUG
		std::cerr << "ERROR: The number of bombs is greater than or equal to the size of the cBoard!\n";
		system("PAUSE");
#endif
		delete[] _square;
		exit(1);
	}
}

cBoard::~cBoard()
{
	delete[] _square;
}

void cBoard::checkMouse(sf::RenderWindow &win)
{
	static bool click = true;
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!click)
		{
			click = true;
			
			cSquare *p = _square;
			for (int i = 0; i < _size; ++i)
			{
				if (p->getRect().getGlobalBounds().contains(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y))
				{
					unsigned short id = (p - _square);
					unsigned short bombsAround = countBombsAround(id / _height, id % _height);

					p->click(bombsAround);

					break;
				}
				++p;
			}
		}
	}
	else
		click = false;
}

void cBoard::display(sf::RenderWindow &win)
{
	cSquare* p = _square;
	for (int i = 0; i < _size; ++i)
		p++->display(win);
}