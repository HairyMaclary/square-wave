#pragma once
#include "./Asteroid/Asteroid.h"

class Laser
{
private:
	sf::RenderWindow& window;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::RectangleShape bolt;

	void hits(Asteroid& asteroid);
	void velocityFromAngle(float angle);

public:
	Laser(
		sf::RenderWindow& renderWindow,
		sf::Vector2f shipPos,
		float shipHeading);
	void update();
	void draw();
	bool offscreen();
	bool hitsAsteroid(Asteroid& asteroid);
};