#include "AI.h"

#include <ctime>

sf::RenderWindow* cAI::_winPointer = NULL;
bool cAI::_isWorking;

cSquare* cAI::_squareGrid = NULL;
unsigned int cAI::_gridWidth, cAI::_gridHeight;

cSquare* cAI::_safeSquare = NULL;


cAI::cAI()
{
	_isWorking = false;
}

cAI::~cAI()
{
	delete _safeSquare;
	delete _winPointer;
}

cAI &cAI::getAI()
{
	static cAI AI;
	return AI;
}

void cAI::firstSquare()
{
	std::srand(time(NULL));
	_safeSquare = &(_squareGrid[std::rand() % (_gridWidth * _gridWidth)]);
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

void cAI::goToSquare()
{
	if (_safeSquare != NULL)
		sf::Mouse::setPosition(sf::Vector2i(_safeSquare->getRect().getPosition()), *_winPointer);
}

void cAI::findSafeSquare()
{
	
}

void cAI::findBomb()
{
	
}

cSquare* cAI::getSafeSquare()
{
	return _safeSquare;
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