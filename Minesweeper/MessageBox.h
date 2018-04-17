#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"
#include "Button.h"

class cMessageBox :public sf::RenderWindow
{
	cText _description;
	cButton _OKButton;

	void mainLoop();
	void display();

public:
	cMessageBox(const sf::String &title, const sf::String &description, const sf::Vector2i &size = {240, 96});
};