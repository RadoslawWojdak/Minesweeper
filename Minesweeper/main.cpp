#include <SFML\Graphics.hpp>
#include <vector>
#include "Board.h"

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper");

	Board board(30, 30, 100);

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
		board.checkMouse(mainWindow);
		
		//Graphics
		mainWindow.clear();

		board.display(mainWindow);

		mainWindow.display();
	}

	return 0;
}