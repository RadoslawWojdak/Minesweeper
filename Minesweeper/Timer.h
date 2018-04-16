#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"

class cTimer
{
	cText _text;
	sf::Clock _clock;
	unsigned int _millisecond;
	bool _paused;

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