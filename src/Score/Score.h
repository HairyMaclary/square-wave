#pragma once

class Score
{
private:
	sf::RenderWindow& window;
	sf::Text scoreBox;
	sf::Font font;
	int currentScore;
	std::string scoreText;

public:
	Score(sf::RenderWindow& renderWindow);
	void draw();
	void update(float radius);
};