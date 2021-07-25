#include "./Score.h"
#include "./Setup/Setup.h" // initial window dimensions and generateSetup()
#include <math.h>		   // round
#include <string>

Score::Score(sf::RenderWindow& renderWindow) :
	window { renderWindow }
{
	if (!font.loadFromFile("src/fonts/open-sans/OpenSans-Regular.ttf"))
	{
		sf::Font::Info info = font.getInfo();
		std::cout << "Bugger, font load did not work" << info.family << std::endl;
	}

	currentScore = 0;
	scoreText = std::to_string(currentScore);
	scoreBox.setFont(font);
	scoreBox.setString(scoreText);
	scoreBox.setCharacterSize(70);
	scoreBox.setFillColor(sf::Color::White);
	scoreBox.setPosition(-windowWidth / 2 * 0.9, -windowHeight / 2 * 0.9);
}

void Score::update(float radius)
{
	currentScore += round(50 - radius);
	scoreText = std::to_string(currentScore);
	scoreBox.setString(scoreText);
}

void Score::draw()
{
	window.draw(scoreBox);
}
