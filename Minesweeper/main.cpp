#include <SFML\Graphics.hpp>
#include "Board.h"
#include "Timer.h"
#include "RestartButton.h"
#include "Text.h"
#include "MessageBox.h"

int main()
{
	if (!cText::init())
	{
		cMessageBox errorMBox("Error 2 - Text init failed!", "Text init failed!");	//The description won't displayed becauese there is no font
		errorMBox.show();
		return 2;
	}

	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

	cBoard board;
	
	while (mainWindow.isOpen())
	{
		cMessageBox sizeMBox("Board size", "Enter the board data", MB_3TEXTBOXES, { "Width", "Height", "Bombs" });
		unsigned short* size = sizeMBox.show().textBox;

		board.newGame(mainWindow, size[0], size[1], size[2]);

		cTimer timer(mainWindow);
		cRestartButton restartButton(sf::Vector2f(mainWindow.getSize().x / 2, 16), 24);
		cText tUnflaggedBombs(sf::Vector2f((int)(mainWindow.getSize().x * 0.25f), 16), "0", 24, sf::Color(48, 48, 224));

		bool closeGame = false;
		bool gameOver = false;
		bool winLoseDisplayed = false;

		timer.restart();
		
		while (!closeGame)
		{
			sf::Mouse::Button mButtonReleased = sf::Mouse::Button::ButtonCount;	//Whatever is not left, middle or right
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
					mButtonReleased = e.mouseButton.button;

					if (restartButton.isMouseOn(mainWindow))
						closeGame = true;
				}
			}

			//Actions
			if (!gameOver)
				board.checkMouse(mainWindow, mButtonReleased, timer, gameOver);

			tUnflaggedBombs.setString(board.getBombs() - board.countFlaggedBombs());

			//Graphics
			mainWindow.clear(sf::Color(191, 191, 191));

			board.display(mainWindow);
			restartButton.display(mainWindow);
			timer.display(mainWindow);
			mainWindow.draw(tUnflaggedBombs);

			mainWindow.display();

			//After the clicked bomb displaying
			if (board.isGameOver() && !winLoseDisplayed)
			{
				gameOver = true;
				timer.pause();

				sf::String mBoxDescription;
				if (board.isBombRevealed())
					mBoxDescription = "Defeat!";
				else
					mBoxDescription = "Victory!";

				cMessageBox gameEndingMBox("GAME OVER", mBoxDescription);
				gameEndingMBox.show();
				winLoseDisplayed = true;
			}
		}
	}

	return 0;
}