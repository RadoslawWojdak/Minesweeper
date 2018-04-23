#include "AI.h"

#include <ctime>

#ifdef _DEBUG
#include <iostream>
#endif

cAI::cAI()
{
#ifdef _DEBUG
	std::cout << "Message: AI has been created! Not started yet!\n";
#endif
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

cSquare* cAI::randomEmptySquare()
{
	for (;;)
	{
		unsigned int random = rand() % (_gridWidth * _gridHeight);

		if (_squareGrid[random].getStatus() != revealed)
			return &(_squareGrid[random]);
	}
}

void cAI::firstSquare()
{
	std::srand(time(NULL));
	_goesToSquare = randomEmptySquare();
}

void cAI::start(sf::RenderWindow &win, cSquare *squareGrid, unsigned int gridWidth, unsigned int gridHeight)
{
#ifdef _DEBUG
	std::cout << "Message: AI has been started!\n";
#endif
	_isWorking = true;
	
	_winPointer = &win;

	_squareGrid = squareGrid;
	_gridWidth = gridWidth;
	_gridHeight = gridHeight;
	
	firstSquare();
}

void cAI::pause()
{
#ifdef _DEBUG
	std::cout << "Message: AI has been paused!\n";
#endif
	_isWorking = false;

	cleanSafeSquares();
	_safeSquare.clear();
}

void cAI::resume()
{
#ifdef _DEBUG
	std::cout << "Message: AI has been resumed!\n";
#endif
	_isWorking = true;
}

void cAI::goToSafeSquare()
{
	if (_isWorking)
	{
		if (_goesToSquare != NULL)
			sf::Mouse::setPosition(sf::Vector2i(_goesToSquare->getRect().getPosition()), *_winPointer);
	}
}

void cAI::findSafeSquare()
{
	if (_isWorking)
	{
		unsigned int gridSize = _gridWidth * _gridHeight;

		short *bombs = new short[gridSize];
		bool *isBomb = new bool[gridSize];
		_safeSquare.clear();
		
		for (unsigned int i = 0; i < gridSize; ++i)
			bombs[i] = _squareGrid[i].getBombNumber();
		for (int i = 0; i < gridSize; ++i)
			isBomb[i] = false;

		
		for (unsigned int i = 0; i < gridSize; ++i)
		{
			sf::Vector2u pos = IDToPos(i);
			
			if (_squareGrid[i].getStatus() == revealed)
				addBombs(pos.x, pos.y, bombs, isBomb);
		}

		int safeSquares = 0;
		for (unsigned int i = 0; i < gridSize; ++i)
		{
			sf::Vector2u pos = IDToPos(i);

			if (_squareGrid[i].getStatus() == unrevealed && isNotBomb(pos.x, pos.y, bombs, isBomb))
			{
				_safeSquare.push_back(&(_squareGrid[i]));
				++safeSquares;
			}
		}

		if (safeSquares > 0)
		{
			int randSquare = rand() % safeSquares;
			_goesToSquare = _safeSquare[randSquare];
		}
		else
			_goesToSquare = randomEmptySquare();

		delete[] bombs;
		delete[] isBomb;
	}
}

std::vector<cSquare*> cAI::getSafeSquares()
{
	return _safeSquare;
}

void cAI::paintSafeSquares(sf::Color col)
{
	if (_isWorking && !_safeSquare.empty())
	{
		for (int i = 0; i < _safeSquare.size(); ++i)
			_safeSquare[i]->setColor(sf::Color(160, 255, 255));
	}
}

void cAI::cleanSafeSquares()
{
	if (!_safeSquare.empty())
	{
		for (int i = 0; i < _safeSquare.size(); ++i)
			_safeSquare[i]->setColor(sf::Color::White);
	}
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

unsigned short cAI::countBombsAround(unsigned int x, unsigned int y, bool* isBomb)
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
					if (_squareGrid[posToID(x - 1, y - 1)].getBombNumber() == countBombsAround(x - 1, y - 1, isBomb))
						return true;
				}
				if (_squareGrid[posToID(x - 1, y)].getStatus() == revealed && _squareGrid[posToID(x - 1, y)].getBombNumber() == countBombsAround(x - 1, y, isBomb))
					return true;
				if (_squareGrid[posToID(x - 1, y + 1)].getStatus() == revealed && y < _gridHeight - 1)
				{
					if (_squareGrid[posToID(x - 1, y + 1)].getBombNumber() == countBombsAround(x - 1, y + 1, isBomb))
						return true;
				}
			}

			if (y > 0)
			{
				if (_squareGrid[posToID(x, y - 1)].getStatus() == revealed && _squareGrid[posToID(x, y - 1)].getBombNumber() == countBombsAround(x, y - 1, isBomb))
					return true;
			}
			if (y < _gridHeight - 1)
			{
				if (_squareGrid[posToID(x, y + 1)].getStatus() == revealed && _squareGrid[posToID(x, y + 1)].getBombNumber() == countBombsAround(x, y + 1, isBomb))
					return true;
			}

			if (x < _gridWidth - 1)
			{
				if (_squareGrid[posToID(x + 1, y - 1)].getStatus() == revealed && y > 0)
				{
					if (_squareGrid[posToID(x + 1, y - 1)].getBombNumber() == countBombsAround(x + 1, y - 1, isBomb))
						return true;
				}
				if (_squareGrid[posToID(x + 1, y)].getStatus() == revealed && _squareGrid[posToID(x + 1, y)].getBombNumber() == countBombsAround(x + 1, y, isBomb))
					return true;
				if (_squareGrid[posToID(x + 1, y + 1)].getStatus() == revealed && y < _gridHeight - 1)
				{
					if (_squareGrid[posToID(x + 1, y + 1)].getBombNumber() == countBombsAround(x + 1, y + 1, isBomb))
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
		if (y > 0 && _squareGrid[posToID(x - 1, y - 1)].getStatus() == unrevealed)
			++sum;
		if (_squareGrid[posToID(x - 1, y)].getStatus() == unrevealed)
			++sum;
		if (y < _gridHeight - 1 && _squareGrid[posToID(x - 1, y + 1)].getStatus() == unrevealed)
			++sum;
	}

	if (y > 0 && _squareGrid[posToID(x, y - 1)].getStatus() == unrevealed)
		++sum;
	if (y < _gridHeight - 1 && _squareGrid[posToID(x, y + 1)].getStatus() == unrevealed)
		++sum;

	if (x < _gridWidth - 1)
	{
		if (y > 0 && _squareGrid[posToID(x + 1, y - 1)].getStatus() == unrevealed)
			++sum;
		if (_squareGrid[posToID(x + 1, y)].getStatus() == unrevealed)
			++sum;
		if (y < _gridHeight - 1 && _squareGrid[posToID(x + 1, y + 1)].getStatus() == unrevealed)
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
			if (y > 0 && _squareGrid[posToID(x - 1, y - 1)].getStatus() == unrevealed)
				isBomb[posToID(x - 1, y - 1)] = true;
			if (_squareGrid[posToID(x - 1, y)].getStatus() == unrevealed)
				isBomb[posToID(x - 1, y)] = true;
			if (y < _gridHeight - 1 && _squareGrid[posToID(x - 1, y + 1)].getStatus() == unrevealed)
				isBomb[posToID(x - 1, y + 1)] = true;
		}

		if (y > 0 && _squareGrid[posToID(x, y - 1)].getStatus() == unrevealed)
			isBomb[posToID(x, y - 1)] = true;
		if (y < _gridHeight - 1 && _squareGrid[posToID(x, y + 1)].getStatus() == unrevealed)
			isBomb[posToID(x, y + 1)] = true;

		if (x < _gridWidth - 1)
		{
			if (y > 0 && _squareGrid[posToID(x + 1, y - 1)].getStatus() == unrevealed)
				isBomb[posToID(x + 1, y - 1)] = true;
			if (_squareGrid[posToID(x + 1, y)].getStatus() == unrevealed)
				isBomb[posToID(x + 1, y)] = true;
			if (y < _gridHeight - 1 && _squareGrid[posToID(x + 1, y + 1)].getStatus() == unrevealed)
				isBomb[posToID(x + 1, y + 1)] = true;
		}
	}
}

bool cAI::isNextToRevealed(unsigned int x, unsigned int y)
{
	if (x > 0)
	{
		if (y > 0 && _squareGrid[posToID(x - 1, y - 1)].getStatus() == revealed)
			return true;
		if (_squareGrid[posToID(x - 1, y)].getStatus() == revealed)
			return true;
		if (y < _gridHeight - 1 && _squareGrid[posToID(x - 1, y + 1)].getStatus() == revealed)
			return true;
	}

	if (y > 0 && _squareGrid[posToID(x, y - 1)].getStatus() == revealed)
		return true;
	if (y < _gridHeight - 1 && _squareGrid[posToID(x, y + 1)].getStatus() == revealed)
		return true;

	if (x < _gridWidth - 1)
	{
		if (y > 0 && _squareGrid[posToID(x + 1, y - 1)].getStatus() == revealed)
			return true;
		if (_squareGrid[posToID(x + 1, y)].getStatus() == revealed)
			return true;
		if (y < _gridHeight - 1 && _squareGrid[posToID(x + 1, y + 1)].getStatus() == revealed)
			return true;
	}

	return false;
}