#include <SFML\Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Timer.h"
#include "RestartButton.h"
#include "Text.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

	if (!cText::init())
	{
#ifdef _DEBUG
		std::cerr << "ERROR: Text init failed!\n";
		system("PAUSE");
#endif
		return 2;
	}

	cBoard board;
	
	while (mainWindow.isOpen())
	{
		board.newGame(mainWindow, 30, 30, 100);

		cTimer timer(mainWindow);
		cRestartButton restartButton(sf::Vector2f(mainWindow.getSize().x / 2, 16), 24);
		cText tUnflaggedBombs(sf::Vector2f((int)(mainWindow.getSize().x * 0.25f), 16), "0", 24, sf::Color(48, 48, 224));

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

			//Actions
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
#endif
			}

			tUnflaggedBombs.setString(board.getBombs() - board.countFlaggedBombs());

			//Graphics
			mainWindow.clear(sf::Color(191, 191, 191));

			board.display(mainWindow, gameOver);
			restartButton.display(mainWindow);
			timer.display(mainWindow);
			mainWindow.draw(tUnflaggedBombs);

			mainWindow.display();
		}
	}

	return 0;
}