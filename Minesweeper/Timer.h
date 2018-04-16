#pragma once

#include <SFML\Graphics.hpp>

class cTimer
{
	static sf::Font _font;

	sf::Text _text;
	sf::Clock _clock;
	bool _started;

	bool init();
	void refreshText(sf::RenderWindow &win);

public:
	cTimer();
	cTimer(sf::RenderWindow &win);

	void start();
	void restart();
	sf::Time getTime();
	void display(sf::RenderWindow &win);
};