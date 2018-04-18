#include "MessageBox.h"

void cMessageBox::display()
{
	this->clear(sf::Color::White);

	_OKButton.display(*this);
	if (_type == MB_3TEXTBOXES)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (_textBox[i].getText().getString().getSize() == 0 && _textBoxString.size() > i)
			{
				sf::Color col = _textBox[i].getTextColor();

				_textBox[i].setString(_textBoxString[i]);
				_textBox[i].setTextColor(sf::Color(164, 164, 164));
				_textBox[i].display(*this);
				_textBox[i].setTextColor(col);
				_textBox[i].setString("");
			}
			else
				_textBox[i].display(*this);
		}
	}
	this->draw(_description);

	this->RenderWindow::display();
}

sf::Vector2u cMessageBox::countSize()
{
	sf::Vector2u size = { 240, 96 };

	if (_type == MB_3TEXTBOXES)
		size.y += 32;

	return size;
}

uThrownData cMessageBox::throwData()
{
	uThrownData data;
	if (MB_3TEXTBOXES)
	{
		data.textBox = new unsigned short[3];
		data.textBox[0] = _textBox[0].getText().getNumber();
		data.textBox[1] = _textBox[1].getText().getNumber();
		data.textBox[2] = _textBox[2].getText().getNumber();
	}
	else
		data.none = true;

	return data;
}

cMessageBox::cMessageBox(const sf::String &title, const sf::String &description, eMBType type, const std::vector <sf::String> &textBoxString)
	: _type(type), sf::RenderWindow(sf::VideoMode(countSize().x, countSize().y), title, sf::Style::Titlebar)
{
	if (countSize() != this->getSize())	//countSize() doesn't work correctly in initialization list
	{
		this->close();
		this->create(sf::VideoMode(countSize().x, countSize().y), title, sf::Style::Titlebar);
	}

	_description = cText(sf::Vector2f(12, 12), description, 16);
	_description.setOrigin(0, 0);
	_OKButton = cButton("OK", sf::Vector2f(this->getSize().x / 2, this->getSize().y - 32), sf::Vector2f(64, 24));

	if (type == MB_3TEXTBOXES)
	{
		_textBox[0] = cTextBox(sf::Vector2f(this->getSize().x / 2 - 80, this->getSize().y - 72), sf::Vector2f(64, 24), true, 5);
		_textBox[1] = cTextBox(sf::Vector2f(this->getSize().x / 2, this->getSize().y - 72), sf::Vector2f(64, 24), true, 5);
		_textBox[2] = cTextBox(sf::Vector2f(this->getSize().x / 2 + 80, this->getSize().y - 72), sf::Vector2f(64, 24), true, 5);
	}
	_textBoxString = textBoxString;
}

uThrownData cMessageBox::show()
{
	bool canClose = true;
	unsigned short active = 1;
	unsigned short textBoxesNumber = 3;
	if (_type == MB_3TEXTBOXES)
	{
		textBoxesNumber = 3;
		canClose = false;
	}

	while (this->isOpen())
	{
		//Events
		sf::Event e;
		while (this->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				if (canClose)
					this->close();
			}
			if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
			{
				active = 0;

				if (canClose && _OKButton.isMouseOn(*this))
					this->close();
				else if (_type == MB_3TEXTBOXES)
				{
					for (int i = 0; i < textBoxesNumber; ++i)
					{
						if (_textBox[i].isMouseOn(*this))
						{
							active = i + 1;
							break;
						}
					}
				}
			}
			if (e.type == sf::Event::KeyPressed)
			{
				if (_type == MB_3TEXTBOXES)
				{
					for (int i = 0; i < textBoxesNumber; ++i)
					{
						if (active == i + 1)
						{
							_textBox[i].putSign(e.key.code);
							break;
						}
					}
				}

				if (e.key.code == sf::Keyboard::Tab)
				{
					active++;
					if (active > textBoxesNumber)
						active = 1;
				}
				else if (e.key.code == sf::Keyboard::Return)
				{
					switch (_type)
					{
					case MB_OK: {this->close(); break;}
					case MB_3TEXTBOXES:
					{
						if (canClose)
							this->close();
						break;
					}
					}
				}
			}
		}

		//Actions
		_OKButton.autoColor(*this);

		if (_type == MB_3TEXTBOXES)
		{
			canClose = true;
			for (int i = 0; i < textBoxesNumber; ++i)
			{
				if (_textBox[i].getText().getNumber() <= 0)
				{
					canClose = false;
					break;
				}
			}
		}

		//Graphics
		this->display();
	}

	return throwData();
}