#include <SFML\Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Timer.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

	cBoard board(mainWindow, 30, 30, 100);
	cTimer timer(mainWindow);

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
			if (e.type == sf::Event::MouseButtonReleased)
			{
				board.checkMouse(mainWindow, e.mouseButton.button, timer);
			}
		}
		
		//Graphics
		mainWindow.clear(sf::Color(191, 191, 191));

		board.display(mainWindow);
		timer.display(mainWindow);

		mainWindow.display();

		//If game is over - behind graphics displaying to display the last square change
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
	}

	return 0;
}