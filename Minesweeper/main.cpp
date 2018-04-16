#include <SFML\Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Timer.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

	cBoard board(mainWindow, 30, 30, 500);
	cTimer timer;

	while (mainWindow.isOpen())
	{
		//Events
		sf::Event e;
		while (mainWindow.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				mainWindow.close();
			}
		}
	
		//Actions
		if (board.isGameOver())
		{
#ifdef _DEBUG
			if (board.isBombRevealed())
				std::cout << "Defeat!\n";
			else
				std::cout << "Victory!\n";
			system("PAUSE");
#endif
			break;
		}

		board.checkMouse(mainWindow);
		
		//Graphics
		mainWindow.clear(sf::Color(191, 191, 191));

		board.display(mainWindow);
		timer.display(mainWindow);

		mainWindow.display();
	}

	return 0;
}