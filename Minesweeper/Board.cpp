#include "Board.h"

#include <ctime>
#include <iostream>

bool* cBoard::_squareChecked;

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
		if (y < _height - 1)
			sum += _square[(x - 1) * _height + y + 1].getBomb();
	}

	if (y > 0)
		sum += _square[x * _height + y - 1].getBomb();
	if (y < _height - 1)
		sum += _square[x * _height + y + 1].getBomb();

	if (x < _width - 1)
	{
		if (y > 0)
			sum += _square[(x + 1) * _height + y - 1].getBomb();
		sum += _square[(x + 1) * _height + y].getBomb();
		if (y < _height - 1)
			sum += _square[(x + 1) * _height + y + 1].getBomb();
	}

	return sum;
}

void cBoard::startAutoDetecting(unsigned short x, unsigned short y)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_square[x * _height + y].click(countBombsAround(x, y));
	}
	else if (_square[x * _height + y].getBomb())
	{
		_square[x * _height + y].click(countBombsAround(x, y));
		if (_square[x * _height + y].getStatus() == revealed)
		{
			_hitBomb = true;
			_gameOver = true;
		}
	}
	else
	{
		clearSquareChecked();
		autoDetecting(x, y);

		for (int i = 0; i < _size; i++)
		{
			if (_squareChecked[i])
				_square[i].click(countBombsAround(i / _height, i % _height));
		}
	}

	if (countCheckedSquares() == _size - _bombs)
		_gameOver = true;
}

void cBoard::autoDetecting(unsigned short x, unsigned short y)
{
	if (!_squareChecked[x * _height + y] && (_square[x * _height + y].getStatus() == unrevealed || _square[x * _height + y].getStatus() == questioned))
	{
		_squareChecked[x * _height + y] = true;
		
		if (countBombsAround(x, y) == 0)
		{
			if (x > 0)
			{
				if (y > 0)
					autoDetecting(x - 1, y - 1);
				autoDetecting(x - 1, y);
				if (y < _height - 1)
					autoDetecting(x - 1, y + 1);
			}

			if (y > 0)
				autoDetecting(x, y - 1);
			if (y < _height - 1)
				autoDetecting(x, y + 1);

			if (x < _width - 1)
			{
				if (y > 0)
					autoDetecting(x + 1, y - 1);
				autoDetecting(x + 1, y);
				if (y < _height - 1)
					autoDetecting(x + 1, y + 1);
			}
		}
	}
}

unsigned int cBoard::countCheckedSquares()
{
	unsigned int sum = 0;
	for (cSquare* p = _square; p < _square + _size; p++)
	{
		if (p->getStatus() == revealed)
			++sum;
	}
	return sum;
}

void cBoard::clearSquareChecked()
{
	for (bool* p = _squareChecked; p < _squareChecked + _size; p++)
		*p = false;
}

cBoard::cBoard(unsigned short width, unsigned short height, unsigned short bombs)
{
	_width = width;
	_height = height;
	_size = width * height;
	_bombs = bombs;
	_hitBomb = false;
	_gameOver = false;
	_square = new cSquare[_size];
	_squareChecked = new bool[_size];

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
		delete[] _squareChecked;
		exit(1);
	}
}

cBoard::~cBoard()
{
	delete[] _square;
	delete[] _squareChecked;
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
					startAutoDetecting(id / _height, id % _height);

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

bool cBoard::isBombRevealed()
{
	return _hitBomb;
}

bool cBoard::isGameOver()
{
	return _gameOver;
}