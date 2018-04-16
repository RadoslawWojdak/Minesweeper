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
	_itoa_s(getTime() / 1000, buffer, 10, 10);
	_text.setString(buffer);
	_text.setPosition((int)(win.getSize().x * 0.8f - _text.getGlobalBounds().width / 2), 2);
}

void cTimer::assignTime()
{
	_millisecond += _clock.getElapsedTime().asMilliseconds();
	_clock.restart();
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
	_millisecond = 0;
	_paused = true;
}


cTimer::cTimer(sf::RenderWindow &win) :cTimer()
{
	refreshText(win);
}

void cTimer::start()
{
	_paused = false;
	_clock.restart();
}

void cTimer::pause()
{
	if (!_paused)
	{
		assignTime();
		_paused = true;
	}
}

void cTimer::restart()
{
	_millisecond = 0;
	_clock.restart();
}

void cTimer::stop()
{
	_paused = true;
	restart();
}

unsigned cTimer::getTime()
{
	return _millisecond + ((!_paused) ? _clock.getElapsedTime().asMilliseconds() : 0);
}

void cTimer::display(sf::RenderWindow &win)
{
	refreshText(win);
	win.draw(_text);
}