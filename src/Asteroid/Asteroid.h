#pragma once

class Asteroid
{
private:
	sf::RenderWindow& window;
	sf::Vector2f velocity;
	sf::Vector2f position { 0.0f, 0.0f };
	// TODO make this static???
	const float maxRadius { 40.0f };
	float localMaxRadius;
	// sf::ConvexShape asteroid;

	void getRandomRadius();
	void getRandomPosition();
	void setUp();
	void randomPointCount();
	void makeAsteroid();
	void randomVelocity();
	void edges();

public:
	uint totalPoints;
	sf::ConvexShape asteroid;

	Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius);
	Asteroid(sf::RenderWindow& window);
	void draw();
	sf::Vector2f getPointTransform(uint pointIndex);
	sf::Vector2f getPosition();
	float getRadius();
};