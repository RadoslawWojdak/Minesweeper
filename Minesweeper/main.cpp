#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Minesweeper");

	while (mainWindow.isOpen())
	{
		sf::Event e;
		while (mainWindow.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				mainWindow.close();
			}
		}

		mainWindow.clear();

		mainWindow.display();
	}

	return 0;
}