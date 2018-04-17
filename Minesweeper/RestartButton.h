#pragma once

#include "Button.h"

class cRestartButton :public cButton
{
public:
	cRestartButton(sf::Vector2f pos, unsigned short size);

	void display(sf::RenderWindow &win);
};