#include "AI.h"

#include <ctime>

#ifdef _DEBUG
#include <iostream>
#endif

cAI::cAI()
{
	_isWorking = false;
}

cAI::~cAI()
{
	_safeSquare.clear();
}

cAI &cAI::getAI()
{
	static cAI AI;
	return AI;
}

void cAI::viewError()
{
	if (!_isWorking)
		std::cerr << "Class cAI ERROR: The cAI::start function was not used!";
}

void cAI::firstSquare()
{
	std::srand(time(NULL));
	_goesToSquare = &(_squareGrid[std::rand() % (_gridWidth * _gridWidth)]);
}

void cAI::start(sf::RenderWindow &win, cSquare *squareGrid, unsigned int gridWidth, unsigned int gridHeight)
{
	_isWorking = true;
	
	_winPointer = &win;

	_squareGrid = squareGrid;
	_gridWidth = gridWidth;
	_gridHeight = gridHeight;
	
	firstSquare();
}

void cAI::goToSafeSquare()
{
	if (_isWorking)
	{
		if (_goesToSquare != NULL)
			sf::Mouse::setPosition(sf::Vector2i(_goesToSquare->getRect().getPosition()), *_winPointer);
	}
#ifdef _DEBUG
	else
		viewError();
#endif
}

void cAI::findSafeSquare()
{
	if (_isWorking)
	{
		short *bombs = new short[_gridWidth * _gridHeight];
		bool *isBomb = new bool[_gridWidth * _gridHeight];
		for (int i = 0; i < _gridWidth * _gridHeight; ++i)
			isBomb[i] = false;
		_safeSquare.clear();

		for (unsigned int i = 0; i < _gridHeight; ++i)
		{
			for (unsigned int j = 0; j < _gridWidth; ++j)
			{
				unsigned int id = posToID(sf::Vector2u(j, i));

				if (_squareGrid[id].getStatus() == revealed)
					bombs[id] = _squareGrid[id].getBombNumber();
				else
					bombs[id] = 0;

				if (bombs[id] == -1)
					bombs[id] = 0;
			}
		}

		for (unsigned int i = 0; i < _gridHeight; ++i)
		{
			for (unsigned int j = 0; j < _gridWidth; ++j)
			{
				unsigned int id = posToID(sf::Vector2u(j, i));

				if (_squareGrid[id].getStatus() == revealed)
					addBombs(j, i, bombs, isBomb);
			}
		}

		int safeSquares = 0;
		for (unsigned int i = 0; i < _gridHeight; ++i)
		{
			for (unsigned int j = 0; j < _gridWidth; ++j)
			{
				unsigned int id = posToID(sf::Vector2u(j, i));

				if (_squareGrid[id].getStatus() == unrevealed)
				{
					if (isNotBomb(j, i, bombs, isBomb))
					{
						_safeSquare.push_back(&(_squareGrid[id]));
						++safeSquares;
					}
				}
			}
		}

		if (safeSquares > 0)
		{
			int randSquare = rand() % safeSquares;
			_goesToSquare = _safeSquare[randSquare];
		}
		else
		{
			for (;;)
			{
				unsigned int random = rand() % (_gridWidth * _gridHeight);

				if (_squareGrid[random].getStatus() != revealed)
				{
					_goesToSquare = &(_squareGrid[random]);
					break;
				}
			}
		}

		delete[] bombs;
		delete[] isBomb;
	}
#ifdef _DEBUG
	else
		viewError();
#endif
}

std::vector<cSquare*> cAI::getSafeSquares()
{
	return _safeSquare;
}

unsigned int cAI::posToID(unsigned int x, unsigned int y)
{
	return posToID(sf::Vector2u(x, y));
}

unsigned int cAI::posToID(sf::Vector2u pos)
{
	return pos.x * _gridHeight + pos.y;
}

sf::Vector2u cAI::IDToPos(unsigned int ID)
{
	sf::Vector2u pos;
	pos.x = ID / _gridHeight;
	pos.y = ID % _gridHeight;
	return pos;
}

unsigned short cAI::countFoundBombsAround(unsigned int x, unsigned int y, bool* isBomb)
{
	int sum = 0;

	if (x > 0)
	{
		if (y > 0)
			sum += isBomb[posToID(x - 1, y - 1)];
		sum += isBomb[posToID(x - 1, y)];
		if (y < _gridHeight - 1)
			sum += isBomb[posToID(x - 1, y + 1)];
	}

	if (y > 0)
		sum += isBomb[posToID(x, y - 1)];
	if (y < _gridHeight - 1)
		sum += isBomb[posToID(x, y + 1)];

	if (x < _gridWidth - 1)
	{
		if (y > 0)
			sum += isBomb[posToID(x + 1, y - 1)];
		sum += isBomb[posToID(x + 1, y)];
		if (y < _gridHeight - 1)
			sum += isBomb[posToID(x + 1, y + 1)];
	}

	return sum;
}

bool cAI::isNotBomb(unsigned int x, unsigned int y, short* bombs, bool* isBomb)
{
	if (isNextToRevealed(x, y))
	{
		unsigned short id = posToID(x, y);

		if (!isBomb[id])
		{
			if (x > 0)
			{
				if (_squareGrid[posToID(x - 1, y - 1)].getStatus() == revealed && y > 0)
				{
					if (_squareGrid[posToID(x - 1, y - 1)].getBombNumber() == countFoundBombsAround(x - 1, y - 1, isBomb))
						return true;
				}
				if (_squareGrid[posToID(x - 1, y)].getStatus() == revealed && _squareGrid[posToID(x - 1, y)].getBombNumber() == countFoundBombsAround(x - 1, y, isBomb))
					return true;
				if (_squareGrid[posToID(x - 1, y + 1)].getStatus() == revealed && y < _gridHeight - 1)
				{
					if (_squareGrid[posToID(x - 1, y + 1)].getBombNumber() == countFoundBombsAround(x - 1, y + 1, isBomb))
						return true;
				}
			}

			if (y > 0)
			{
				if (_squareGrid[posToID(x, y - 1)].getStatus() == revealed && _squareGrid[posToID(x, y - 1)].getBombNumber() == countFoundBombsAround(x, y - 1, isBomb))
					return true;
			}
			if (y < _gridHeight - 1)
			{
				if (_squareGrid[posToID(x, y + 1)].getStatus() == revealed && _squareGrid[posToID(x, y + 1)].getBombNumber() == countFoundBombsAround(x, y + 1, isBomb))
					return true;
			}

			if (x < _gridWidth - 1)
			{
				if (_squareGrid[posToID(x + 1, y - 1)].getStatus() == revealed && y > 0)
				{
					if (_squareGrid[posToID(x + 1, y - 1)].getBombNumber() == countFoundBombsAround(x + 1, y - 1, isBomb))
						return true;
				}
				if (_squareGrid[posToID(x + 1, y)].getStatus() == revealed && _squareGrid[posToID(x + 1, y)].getBombNumber() == countFoundBombsAround(x + 1, y, isBomb))
					return true;
				if (_squareGrid[posToID(x + 1, y + 1)].getStatus() == revealed && y < _gridHeight - 1)
				{
					if (_squareGrid[posToID(x + 1, y + 1)].getBombNumber() == countFoundBombsAround(x + 1, y + 1, isBomb))
						return true;
				}
			}
		}
	}

	return false;
}

unsigned short cAI::countEmptiesAround(unsigned int x, unsigned int y)
{
	int sum = 0;

	if (x > 0)
	{
		if (y > 0 && _squareGrid[(x - 1) * _gridHeight + y - 1].getStatus() == unrevealed)
			++sum;
		if (_squareGrid[(x - 1) * _gridHeight + y].getStatus() == unrevealed)
			++sum;
		if (y < _gridHeight - 1 && _squareGrid[(x - 1) * _gridHeight + y + 1].getStatus() == unrevealed)
			++sum;
	}

	if (y > 0 && _squareGrid[x * _gridHeight + y - 1].getStatus() == unrevealed)
		++sum;
	if (y < _gridHeight - 1 && _squareGrid[x * _gridHeight + y + 1].getStatus() == unrevealed)
		++sum;

	if (x < _gridWidth - 1)
	{
		if (y > 0 && _squareGrid[(x + 1) * _gridHeight + y - 1].getStatus() == unrevealed)
			++sum;
		if (_squareGrid[(x + 1) * _gridHeight + y].getStatus() == unrevealed)
			++sum;
		if (y < _gridHeight - 1 && _squareGrid[(x + 1) * _gridHeight + y + 1].getStatus() == unrevealed)
			++sum;
	}

	return sum;
}

void cAI::addBombs(unsigned int x, unsigned int y, short *bombs, bool* isBomb)
{
	unsigned int id = posToID(sf::Vector2u(x, y));

	if (bombs[id] == countEmptiesAround(x, y))
	{
		if (x > 0)
		{
			if (y > 0 && _squareGrid[(x - 1) * _gridHeight + y - 1].getStatus() == unrevealed)
				isBomb[posToID(x - 1, y - 1)] = true;
			if (_squareGrid[(x - 1) * _gridHeight + y].getStatus() == unrevealed)
				isBomb[posToID(x - 1, y)] = true;
			if (y < _gridHeight - 1 && _squareGrid[(x - 1) * _gridHeight + y + 1].getStatus() == unrevealed)
				isBomb[posToID(x - 1, y + 1)] = true;
		}

		if (y > 0 && _squareGrid[x * _gridHeight + y - 1].getStatus() == unrevealed)
			isBomb[posToID(x, y - 1)] = true;
		if (y < _gridHeight - 1 && _squareGrid[x * _gridHeight + y + 1].getStatus() == unrevealed)
			isBomb[posToID(x, y + 1)] = true;

		if (x < _gridWidth - 1)
		{
			if (y > 0 && _squareGrid[(x + 1) * _gridHeight + y - 1].getStatus() == unrevealed)
				isBomb[posToID(x + 1, y - 1)] = true;
			if (_squareGrid[(x + 1) * _gridHeight + y].getStatus() == unrevealed)
				isBomb[posToID(x + 1, y)] = true;
			if (y < _gridHeight - 1 && _squareGrid[(x + 1) * _gridHeight + y + 1].getStatus() == unrevealed)
				isBomb[posToID(x + 1, y + 1)] = true;
		}
	}
}

bool cAI::isNextToRevealed(unsigned int x, unsigned int y)
{
	if (x > 0)
	{
		if (y > 0 && _squareGrid[(x - 1) * _gridHeight + y - 1].getStatus() == revealed)
			return true;
		if (_squareGrid[(x - 1) * _gridHeight + y].getStatus() == revealed)
			return true;
		if (y < _gridHeight - 1 && _squareGrid[(x - 1) * _gridHeight + y + 1].getStatus() == revealed)
			return true;
	}

	if (y > 0 && _squareGrid[x * _gridHeight + y - 1].getStatus() == revealed)
		return true;
	if (y < _gridHeight - 1 && _squareGrid[x * _gridHeight + y + 1].getStatus() == revealed)
		return true;

	if (x < _gridWidth - 1)
	{
		if (y > 0 && _squareGrid[(x + 1) * _gridHeight + y - 1].getStatus() == revealed)
			return true;
		if (_squareGrid[(x + 1) * _gridHeight + y].getStatus() == revealed)
			return true;
		if (y < _gridHeight - 1 && _squareGrid[(x + 1) * _gridHeight + y + 1].getStatus() == revealed)
			return true;
	}

	return false;
}