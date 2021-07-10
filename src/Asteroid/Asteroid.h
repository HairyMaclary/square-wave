#pragma once

class Asteroid
{
private:
	sf::RenderWindow& window;
	sf::Vector2f position;
	float radius;
	// TODO make this static???
	const float maxRadius { 100.0f };
	float localMaxRadius;
	uint totalPoints;
	sf::ConvexShape asteroid;

	void getRandomRadius();
	void getRandomPosition();
	void setUp();
	void getTotalPointCount();
	void makeAsteroid();

public:
	Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius);
	Asteroid(sf::RenderWindow& window);
	void draw();
};