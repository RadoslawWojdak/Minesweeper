#pragma once

#include <SFML\Graphics.hpp>
#include "Text.h"
#include "Button.h"
#include "TextBox.h"

enum eMBType { MB_OK, MB_3TEXTBOXES };

union uThrownData
{
	bool none;
	unsigned short* textBox;
};

class cMessageBox :public sf::RenderWindow
{
	static const unsigned short TEXTBOXES = 3;

	eMBType _type;

	cText _description;
	cButton _OKButton;
	cTextBox _textBox[TEXTBOXES];

	void display();
	sf::Vector2u countSize();

	uThrownData throwData();

public:
	cMessageBox(const sf::String &title = "", const sf::String &description = "", eMBType type = MB_OK);

	uThrownData show();
};