#pragma once

#include "Square.h"
#include "Timer.h"

class cBoard
{
	static bool* _squareChecked;	//Checks whether the square has already been checked in the autoDetecting function

	cSquare* _square;
	unsigned int _size;
	unsigned short _width, _height;
	unsigned int _bombs;
	bool _hitBomb, _gameOver;
	bool _firstClick;

	void randBombs(unsigned short clickX, unsigned short clickY);
	void randomizeBombs(unsigned short clickX, unsigned short clickY);
	unsigned short countBombsAround(unsigned short x, unsigned short y);
	void startAutoDetecting(unsigned short x, unsigned short y, cTimer &timer);
	void autoDetecting(unsigned short x, unsigned short y);
	unsigned int countCheckedSquares();
	void clearSquareChecked();
	void adjustWindowSize(sf::RenderWindow &win, unsigned short squareSize);

public:
	cBoard(sf::RenderWindow &win, unsigned short width, unsigned short height, unsigned short bombs);
	~cBoard();

	void checkMouse(sf::RenderWindow &win, cTimer &timer);
	void display(sf::RenderWindow &win);

	bool isBombRevealed();
	bool isGameOver();
};