#include "MessageBox.h"

void cMessageBox::mainLoop()
{
	while (this->isOpen())
	{
		//Events
		sf::Event e;
		while (this->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				this->close();
			if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
			{
				if (_OKButton.isMouseOn(*this))
					this->close();
			}
		}

		//Actions
		_OKButton.autoColor(*this);

		//Graphics
		this->display();
	}
}

void cMessageBox::display()
{
	this->clear(sf::Color::White);

	_OKButton.display(*this);
	this->draw(_description);

	this->RenderWindow::display();
}

cMessageBox::cMessageBox(const sf::String &title, const sf::String &description, const sf::Vector2i &size) 
	: sf::RenderWindow(sf::VideoMode(size.x, size.y), title, sf::Style::Titlebar)
{
	_description = cText(sf::Vector2f(12, 12), description, 16);
	_description.setOrigin(0, 0);
	_OKButton = cButton("OK", sf::Vector2f(this->getSize().x / 2, this->getSize().y - 32), sf::Vector2f(64, 24));

	mainLoop();
}