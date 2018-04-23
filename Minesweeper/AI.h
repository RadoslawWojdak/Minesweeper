#pragma once

#include <SFML\Graphics.hpp>
#include "Square.h"

class cAI
{
	static sf::RenderWindow* _winPointer;
	static bool _isWorking;

	static cSquare* _squareGrid;
	static unsigned int _gridWidth, _gridHeight;

	static cSquare* _safeSquare;

	cAI();
	cAI(const cAI &other) {};

	static void firstSquare();
	static unsigned int posToID(sf::Vector2u pos);
	static sf::Vector2u IDToPos(unsigned int ID);

public:
	~cAI();
	static cAI &getAI();

	static void start(sf::RenderWindow &win, cSquare *squareGrid, unsigned int gridWidth, unsigned int _ridHeight);
	static void goToSquare();
	static void findSafeSquare();
	static void findBomb();
	
	cSquare* getSafeSquare();
};