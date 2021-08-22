#pragma once

#include <string>

class ArrowControl
{

private:
	sf::Font font;
	sf::Font arrowFont;
	sf::RenderWindow& window;
	uint& circleCount;
	sf::Text text;

	sf::Text arrow;

public:
	ArrowControl(sf::RenderWindow& renderWindow, uint& initialCount) :
		window { renderWindow },
		circleCount { initialCount }
	{

		font.loadFromFile("src/fonts/open-sans/OpenSans-Regular.ttf");
		arrowFont.loadFromFile("src/fonts/open-symbol/911Fonts.com_OpenSymbolRegular__-_911fonts.com_fonts_5hBf.ttf");

		text.setString("Hello");
		text.setFont(font);
		text.setCharacterSize(50);
		text.setPosition(sf::Vector2f(350.f, -250.f));

		arrow.setString(L"↕");
		arrow.setFont(arrowFont);
		arrow.setCharacterSize(50);
		arrow.setPosition(sf::Vector2f(320.f, -250.f));
	}

	void update()
	{
		std::string count = std::to_string(circleCount);
		text.setString(count);
	}

	void draw()
	{
		window.draw(text);
		window.draw(arrow);
	}

	void increase()
	{
		if (circleCount < 2000)
		{
			circleCount++;
		}
	}

	void decrease()
	{
		if (circleCount > 1)
		{
			circleCount--;
		}
	}
};