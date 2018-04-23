#include <SFML\Graphics.hpp>
#include "Board.h"
#include "Timer.h"
#include "Text.h"
#include "MessageBox.h"
#include "AI.h"

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
		struct
		{
			unsigned int width, height;
			unsigned int bombs;
		} boardData;

		bool bombsFits = false;
		while (!bombsFits)
		{
			cMessageBox sizeMBox("Board size", "Enter the board data", MB_3TEXTBOXES, { "Width", "Height", "Bombs" });
			unsigned short* data = sizeMBox.show().textBox;
			
			boardData.width = data[0];
			boardData.height = data[1];
			boardData.bombs = data[2];

			if (boardData.width * boardData.height > boardData.bombs)
				bombsFits = true;
			else
			{
				cMessageBox errorMBox("Error", "The number of bombs is greater than or equal to the size of the board!");
				errorMBox.show();
			}
		}


		board.newGame(mainWindow, boardData.width, boardData.height, boardData.bombs);

		cTimer timer(mainWindow);
		cButton restartButton("R", sf::Vector2f(mainWindow.getSize().x / 2 - 0, 16), sf::Vector2f(24, 24));
		cButton paintAIButton("ON", sf::Vector2f(mainWindow.getSize().x / 2 - 48, 16), sf::Vector2f(48, 24));
		cButton mouseAIButton("ON", sf::Vector2f(mainWindow.getSize().x / 2 + 48, 16), sf::Vector2f(48, 24));
		cText tUnflaggedBombs(sf::Vector2f((int)(mainWindow.getSize().x * 0.25f), 16), "0", 24, sf::Color(48, 48, 224));

		bool closeGame = false;
		bool gameOver = false;
		bool winLoseDisplayed = false;
		bool paintAI = false;
		bool mouseAI = false;
		bool allAIOff = true;

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
					if (paintAIButton.isMouseOn(mainWindow))
					{
						if (paintAIButton.getString() == "ON")
						{
							paintAIButton.setString("OFF");
							paintAI = true;
						}
						else
						{
							paintAIButton.setString("ON");
							paintAI = false;
						}
					}
					if (mouseAIButton.isMouseOn(mainWindow))
					{
						if (mouseAIButton.getString() == "ON")
						{
							mouseAIButton.setString("OFF");
							mouseAI = true;
						}
						else
						{
							mouseAIButton.setString("ON");
							mouseAI = false;
						}
					}
				}
				if (e.type == sf::Event::KeyPressed)	//Turn off mouse AI mode
				{
					if (e.key.code == sf::Keyboard::Escape)
					{
						mouseAIButton.setString("ON");
						mouseAI = false;
					}
				}
			}

			//Actions
			if (paintAI || mouseAI)
			{
				if (allAIOff)
				{
					cAI::getAI().resume();
					allAIOff = false;
				}
			}
			else if (!allAIOff)
			{
				cAI::getAI().pause();
				allAIOff = true;
			}

			if (!gameOver)
			{
				if (mouseAI)
				{
					cAI::getAI().findSafeSquare();

					sf::Clock clock;
					while (clock.getElapsedTime().asMilliseconds() < 750)
					{
						cAI::getAI().goToSafeSquare();
					}
					mButtonReleased = sf::Mouse::Left;
				}

				board.checkMouse(mainWindow, mButtonReleased, timer, gameOver);

				if (paintAI && mButtonReleased == sf::Mouse::Left)
				{
					cAI::getAI().findSafeSquare();
					cAI::getAI().paintSafeSquares();
				}
			}

			tUnflaggedBombs.setString(board.getBombs() - board.countFlaggedBombs());

			//Graphics
			mainWindow.clear(sf::Color(191, 191, 191));

			board.display(mainWindow);
			restartButton.display(mainWindow);
			paintAIButton.display(mainWindow);
			mouseAIButton.display(mainWindow);
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