#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Square.h"

class cAI
{
	sf::RenderWindow* _winPointer;
	bool _isWorking;

	cSquare* _squareGrid;
	unsigned int _gridWidth, _gridHeight;

	std::vector<cSquare*> _safeSquare;
	cSquare* _goesToSquare;


	cAI();
	cAI(const cAI &other) {};

	void viewError();
	void firstSquare();
	unsigned int posToID(unsigned int x, unsigned int y);
	unsigned int posToID(sf::Vector2u pos);
	sf::Vector2u IDToPos(unsigned int ID);
	unsigned short countFoundBombsAround(unsigned int x, unsigned int y, bool* isBomb);
	unsigned short countEmptiesAround(unsigned int x, unsigned int y);
	bool isNextToRevealed(unsigned int x, unsigned int y);
	void addBombs(unsigned int x, unsigned int y, short *bombs, bool* isBomb);
	bool isNotBomb(unsigned int x, unsigned int y, short* bombs, bool* isBomb);

public:
	~cAI();
	static cAI &getAI();

	void start(sf::RenderWindow &win, cSquare *squareGrid, unsigned int gridWidth, unsigned int _ridHeight);
	void goToSafeSquare();
	void findSafeSquare();
	
	std::vector<cSquare*> getSafeSquares();
};