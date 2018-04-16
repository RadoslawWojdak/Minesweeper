#include "Board.h"

#include <ctime>
#include <iostream>
#include <cmath>

bool* cBoard::_squareChecked;

void cBoard::randBombs(unsigned short clickX, unsigned short clickY)
{
	srand(time(NULL));

	for (unsigned short i = 0; i < _bombs;)
	{
		int rnd = rand() % _size;
		if (!_square[rnd].getBomb() && (clickX * _height + clickY != rnd))
		{
			_square[rnd].setBomb();
			++i;
		}
	}
}

void cBoard::randomizeBombs(unsigned short clickX, unsigned short clickY)
{
	if (_width * _height > _bombs)
		randBombs(clickX, clickY);
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

void cBoard::startAutoDetecting(unsigned short x, unsigned short y, sf::Mouse::Button buttonReleased, cTimer &timer)
{
	if (!buttonReleased == sf::Mouse::Button::Left)
	{
		_square[x * _height + y].click(countBombsAround(x, y), buttonReleased);
	}
	else if (_square[x * _height + y].getBomb())
	{
		_square[x * _height + y].click(countBombsAround(x, y), buttonReleased);
		if (_square[x * _height + y].getStatus() == revealed)
		{
			_hitBomb = true;
			_gameOver = true;
		}
	}
	else
	{
		if (!_firstClick)
		{
			_firstClick = true;
			randomizeBombs(x, y);
			timer.start();
		}

		clearSquareChecked();
		autoDetecting(x, y);

		for (int i = 0; i < _size; i++)
		{
			if (_squareChecked[i])
				_square[i].click(countBombsAround(i / _height, i % _height), buttonReleased);
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

void cBoard::adjustWindowSize(sf::RenderWindow &win, unsigned short squareSize)
{
	if (win.isOpen())
		win.close();
	win.create(sf::VideoMode(squareSize * _width, squareSize * _height + 32), "Minesweeper", sf::Style::Close);
}

unsigned short cBoard::adjustSquareToResolution()
{
	sf::Vector2i screenResolution;
	screenResolution.x = sf::VideoMode::getDesktopMode().width;
	screenResolution.y = sf::VideoMode::getDesktopMode().height;

	unsigned short squareSize = 16;
	if (squareSize * _width > screenResolution.x)
		squareSize = screenResolution.x / _width;
	if (squareSize * _height + 32 > screenResolution.y)	//Not "else if" - still can be too big
		squareSize = screenResolution.y / _height;

	return squareSize;
}

void cBoard::deletePointers()
{
	if (_square != NULL)
	{
		delete[] _square;
		_square = NULL;
	}
	if (_squareChecked != NULL)
	{
		delete[] _squareChecked;
		_squareChecked = NULL;
	}
}

cBoard::cBoard(sf::RenderWindow &win, unsigned short width, unsigned short height, unsigned short bombs)
{
	newGame(win, width, height, bombs);
}

cBoard::~cBoard()
{
	deletePointers();
}

void cBoard::checkMouse(sf::RenderWindow &win, sf::Mouse::Button buttonReleased, cTimer &timer)
{
	if (buttonReleased == sf::Mouse::Left || buttonReleased == sf::Mouse::Middle || buttonReleased == sf::Mouse::Right)
	{
		cSquare *p = _square;
		for (int i = 0; i < _size; ++i)
		{
			if (p->getRect().getGlobalBounds().contains(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y))
			{
				unsigned short id = (p - _square);
				startAutoDetecting(id / _height, id % _height, buttonReleased, timer);

				break;
			}
			++p;
		}
	}
}

void cBoard::newGame(sf::RenderWindow &win, unsigned short width, unsigned short height, unsigned short bombs)
{
	_width = width;
	_height = height;
	_size = width * height;
	_bombs = bombs;
	_hitBomb = false;
	_gameOver = false;
	_firstClick = false;

	deletePointers();
	_square = new cSquare[_size];
	_squareChecked = new bool[_size];

	unsigned short squareSize = adjustSquareToResolution();
	adjustWindowSize(win, squareSize);

	sf::Vector2f boardStartPos;
	boardStartPos.x = win.getSize().x / 2 - (squareSize * width) / 2;
	boardStartPos.y = 32;

	cSquare* p = _square;
	for (unsigned short i = 0; i < width; ++i)
	{
		for (unsigned short j = 0; j < height; ++j)
			*p++ = cSquare(i, j, boardStartPos, squareSize);
	}
}

void cBoard::display(sf::RenderWindow &win, bool gameOver)
{
	cSquare* p = _square;
	for (int i = 0; i < _size; ++i)
		p++->display(win, gameOver);
}

bool cBoard::isBombRevealed()
{
	return _hitBomb;
}

bool cBoard::isGameOver()
{
	return _gameOver;
}