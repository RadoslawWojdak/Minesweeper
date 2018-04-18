#pragma once

#include "Square.h"
#include "Timer.h"

class cSquare;

class cBoard
{
	static bool* _squareChecked;	//Checks whether the square has already been checked in the autoDetecting function
	cSquare* _lastOnMouseSquare;	//Needed to clean the color of clicked rectangle

	cSquare* _square;
	sf::Vector2f _startPosition;
	unsigned int _size;
	unsigned int _width, _height;
	unsigned int _bombs;
	unsigned int _flaggedBombs;
	bool _hitBomb, _gameOver;
	bool _firstClick;

	void randBombs(unsigned int clickX, unsigned int clickY);
	void randomizeBombs(unsigned int clickX, unsigned int clickY);
	unsigned short countBombsAround(unsigned int x, unsigned int y);
	void startAutoDetecting(unsigned int x, unsigned int y, sf::Mouse::Button buttonReleased, cTimer &timer);
	void autoDetecting(unsigned int x, unsigned int y);
	unsigned int countCheckedSquares();
	void clearSquareChecked();
	void adjustWindowSize(sf::RenderWindow &win, unsigned short squareSize);
	unsigned short adjustSquareToResolution();
	void deletePointers();

public:
	cBoard() {};
	cBoard(sf::RenderWindow &win, unsigned int width, unsigned int height, unsigned int bombs);
	~cBoard();

	void checkMouse(sf::RenderWindow &win, sf::Mouse::Button buttonReleased, cTimer &timer, bool isGameOver);
	void newGame(sf::RenderWindow &win, unsigned int width, unsigned int height, unsigned int bombs);
	void display(sf::RenderWindow &win);

	unsigned int getBombs();
	unsigned int countFlaggedBombs();
	sf::Vector2i getMouseSquare(sf::RenderWindow &win);
	bool isBombRevealed();
	bool isGameOver();
};