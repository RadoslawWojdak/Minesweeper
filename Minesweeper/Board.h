#pragma once

#include "Square.h"

class cBoard
{
	cSquare* _square;
	unsigned int _size;
	unsigned short _width, _height;

	void randBombs(unsigned short number);
	unsigned short countBombsAround(unsigned short x, unsigned short y);
	void startAutoDetecting(unsigned short x, unsigned short y);
	void autoDetecting(unsigned short x, unsigned short y);

public:
	cBoard(unsigned short width, unsigned short height, unsigned short bombs);
	~cBoard();

	void checkMouse(sf::RenderWindow &win);
	void display(sf::RenderWindow &win);
};