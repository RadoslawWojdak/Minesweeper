#include "Timer.h"
#include <iostream>

sf::Font cTimer::_font;

bool cTimer::init()
{
	if (!_font.loadFromFile("font.ttf"))
	{
#ifdef _DEBUG
		std::cerr << "ERROR: File \"arial.ttf\" not found!\n";
#endif
		return false;
	}

	return true;
}

void cTimer::refreshText(sf::RenderWindow &win)
{
	char buffer[10];
	_itoa_s(getTime().asSeconds(), buffer, 10, 10);
	_text.setString(buffer);
	_text.setPosition((int)(win.getSize().x / 2 - _text.getGlobalBounds().width / 2), 2);
}

cTimer::cTimer()
{
	restart();

	static bool init = false;
	if (!init)
	{
		init = true;
		if (!cTimer::init())
		{
#ifdef _DEBUG
			std::cerr << "ERROR: Timer init error!\n";
			system("PAUSE");
#endif
			exit(3);
		}
	}

	_text.setFont(_font);
	_text.setFillColor(sf::Color(65, 65, 65));
	_text.setCharacterSize(24);
	_text.setString("0");
	_started = false;
}


cTimer::cTimer(sf::RenderWindow &win) :cTimer()
{
	refreshText(win);
}

void cTimer::start()
{
	_started = true;
	restart();
}

void cTimer::restart()
{
	_clock.restart();
}

sf::Time cTimer::getTime()
{
	return _clock.getElapsedTime();
}

void cTimer::display(sf::RenderWindow &win)
{
	if (_started)
		refreshText(win);
	win.draw(_text);
}