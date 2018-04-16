#include "Timer.h"

void cTimer::refreshText(sf::RenderWindow &win)
{
	_text.setString(getTime() / 1000);
}

void cTimer::assignTime()
{
	_millisecond += _clock.getElapsedTime().asMilliseconds();
	_clock.restart();
}

cTimer::cTimer()
{
	restart();

	_text = cText({ 0,0 }, "0", 24, sf::Color(65, 65, 65));

	_millisecond = 0;
	_paused = true;
}

cTimer::cTimer(sf::RenderWindow &win) :cTimer()
{
	_text.setPosition((int)(win.getSize().x * 0.75f), 16);
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