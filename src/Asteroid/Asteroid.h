#pragma once

class Asteroid
{
private:
	sf::RenderWindow& window;
	sf::Vector2f position { 0.0f, 0.0f };
	sf::Vector2f velocity;
	float radius;
	// TODO make this static???
	const float maxRadius { 40.0f };
	float localMaxRadius;
	uint totalPoints;
	sf::ConvexShape asteroid;

	void getRandomRadius();
	void getRandomPosition();
	void setUp();
	void getTotalPointCount();
	void makeAsteroid();
	void randomVelocity();
	void edges();

public:
	Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius);
	Asteroid(sf::RenderWindow& window);
	void draw();
	sf::FloatRect getGlobalBounds();
};