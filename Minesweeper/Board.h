#pragma once

#include "Square.h"

class cBoard
{
	static bool* _squareChecked;	//Checks whether the square has already been checked in the autoDetecting function

	cSquare* _square;
	unsigned int _size;
	unsigned short _width, _height;
	unsigned int _bombs;
	bool _hitBomb, _gameOver;

	void randBombs(unsigned short number);
	unsigned short countBombsAround(unsigned short x, unsigned short y);
	void startAutoDetecting(unsigned short x, unsigned short y);
	void autoDetecting(unsigned short x, unsigned short y);
	unsigned int countCheckedSquares();
	void clearSquareChecked();
	void adjustWindowSize(sf::RenderWindow &win, unsigned short squareSize);

public:
	cBoard(sf::RenderWindow &win, unsigned short width, unsigned short height, unsigned short bombs);
	~cBoard();

	void checkMouse(sf::RenderWindow &win);
	void display(sf::RenderWindow &win);

	bool isBombRevealed();
	bool isGameOver();
};