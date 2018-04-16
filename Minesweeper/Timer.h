#pragma once

#include <SFML\Graphics.hpp>

class cTimer
{
	static sf::Font _font;

	sf::Text _text;
	sf::Clock _clock;
	unsigned int _millisecond;
	bool _paused;

	bool init();
	void refreshText(sf::RenderWindow &win);
	void assignTime();

public:
	cTimer();
	cTimer(sf::RenderWindow &win);

	void start();
	void pause();
	void stop();
	void restart();
	unsigned int getTime();
	void display(sf::RenderWindow &win);
};