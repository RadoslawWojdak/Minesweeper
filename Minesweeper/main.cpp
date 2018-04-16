#include <SFML\Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Timer.h"
#include "RestartButton.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

	cTimer timer(mainWindow);

	while (mainWindow.isOpen())
	{
		cBoard board(mainWindow, 30, 30, 100);
		cRestartButton restartButton(sf::Vector2i(mainWindow.getSize().x / 2, 16), 24);

		bool closeGame = false;
		bool gameOver = false;
		bool winLoseDisplayed = false;

		timer.restart();
		
		while (!closeGame)
		{
			//Events
			sf::Event e;
			while (mainWindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					mainWindow.close();
					closeGame = true;
				}
				if (e.type == sf::Event::MouseButtonReleased)
				{
					sf::Mouse::Button mButton = e.mouseButton.button;

					if (!gameOver)
						board.checkMouse(mainWindow, mButton, timer);
					if (restartButton.click(mainWindow, mButton))
						closeGame = true;
				}
			}

			//Graphics
			mainWindow.clear(sf::Color(191, 191, 191));

			board.display(mainWindow, gameOver);
			timer.display(mainWindow);
			restartButton.display(mainWindow);

			mainWindow.display();

			//If game is over - behind graphics displaying to display the last square change
			if (board.isGameOver())
			{
				gameOver = true;
				timer.pause();
#ifdef _DEBUG
				if (!winLoseDisplayed)
				{
					winLoseDisplayed = true;
					if (board.isBombRevealed())
						std::cout << "Defeat!\n";
					else
						std::cout << "Victory!\n";
				}
			}
#endif
		}
	}

	return 0;
}