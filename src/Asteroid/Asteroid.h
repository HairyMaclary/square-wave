#pragma once

class Asteroid
{
private:
	sf::Vector2f position;
	float radius;
	const float maxRadius { 50.0f };

	void getRandomRadius();
	void getRandomPosition();

public:
	Asteroid(sf::Vector2f position, float radius);
	Asteroid();
};