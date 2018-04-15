#pragma once

#include "Square.h"

class Board
{
	cSquare* _square;
	unsigned int _size;

	void randBombs(unsigned short number);

public:
	Board(unsigned short width, unsigned short height, unsigned short bombs);
	~Board();

	void checkMouse(sf::RenderWindow &win);
	void display(sf::RenderWindow &win);
};