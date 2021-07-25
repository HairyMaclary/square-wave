#pragma once

#include "./Laser/Laser.h"

class Asteroid
{
private:
	sf::RenderWindow& window;
	sf::Vector2f velocity;
	sf::Vector2f position { 0.0f, 0.0f };
	const float maxRadius { 40.0f };
	float localMaxRadius;
	// Never drawn. Only for collision detection
	std::vector<sf::RectangleShape> boundaryLines;
	sf::ConvexShape asteroid;
	uint totalPoints;

	void getRandomRadius();
	void getRandomPosition(sf::Vector2f shipPos);
	void setUp();
	void randomPointCount();
	void makeAsteroid();
	void randomVelocity();
	void edges();
	void makeCollisonBoundary();

public:
	Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius);
	Asteroid(sf::RenderWindow& window, sf::Vector2f& shipPos);
	void draw();
	sf::Vector2f getPointTransform(uint pointIndex);
	sf::Vector2f getPosition();
	float getRadius();
	bool hit(const sf::FloatRect& bounds);
};