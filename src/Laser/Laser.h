#pragma once

class Laser
{
private:
	sf::RenderWindow& window;
	sf::RectangleShape bolt;
	sf::Vector2f position;
	sf::Vector2f velocity;

	void velocityFromAngle(float angle);

public:
	Laser(
		sf::RenderWindow& renderWindow,
		sf::Vector2f shipPos,
		float shipHeading);
	void update();
	void draw();
	bool offscreen();
	sf::FloatRect getGlobalBounds();
};