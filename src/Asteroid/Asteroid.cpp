#include "./Asteroid.h"
#include "Setup/Setup.h" /* windowWidth, windowHeight */
#include <stdlib.h>		 /* srand, rand */
#include <time.h>		 /* time */

//TODO central location for this vector stuff. Also used in ship.cpp.
// Possibly even consider extending sf::vector with p5 like functionality.
const float pi = float(std::atan(1) * 4);

void Asteroid::getRandomPosition()
{
	position.x = (float)std::rand() / RAND_MAX * windowWidth - (windowWidth / 2);
	position.y = (float)std::rand() / RAND_MAX * windowHeight - (windowHeight / 2);
}

// Asteroid::Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius) :
// 	window { window },
// 	position { position },
// 	localMaxRadius { radius }
// {
// 	setUp();
// }

Asteroid::Asteroid(sf::RenderWindow& window) :
	window { window },
	localMaxRadius { maxRadius }
{
	getRandomPosition();
	setUp();
}

void Asteroid::draw()
{
	edges();
	float newPosX = velocity.x + position.x;
	float newPosY = position.y + velocity.y;
	// position.x = newPosX;
	// position.y = newPosY;
	// this->position = sf::Vector2f(newPosX, newPosY);
	asteroid.setPosition(newPosX, newPosY);
	position.x = newPosX;
	position.y = newPosY;
	asteroid.setPosition(position.x, position.y);

	window.draw(asteroid);
}

void Asteroid::setUp()
{
	getTotalPointCount();
	makeAsteroid();
	randomVelocity();
}

void Asteroid::getTotalPointCount()
{
	const uint maxBasePoints = 15;
	const uint minPoints = 5; // 15 + 5 will given a max of 20 points
	totalPoints = std::round((float)std::rand() / RAND_MAX * maxBasePoints) + minPoints;
}

void Asteroid::makeAsteroid()
{
	// totalPoints = 4;
	asteroid.setPointCount(totalPoints);

	const float radiansPerPoint = 2 * pi / totalPoints;

	for (uint i = 0; i < totalPoints; i++)
	{
		const float minDistance = 15.0f;
		const float pointDistance = (float)std::rand() / RAND_MAX * localMaxRadius + minDistance;
		const float angle = (i + 1) * radiansPerPoint;
		const float xPos = pointDistance * std::sin(angle);
		const float yPos = pointDistance * -std::cos(angle);
		sf::Vector2f relativeVector(xPos, yPos);
		asteroid.setPoint(i, relativeVector);
	}
	// asteroid.setRadius(radius);
	asteroid.setFillColor(sf::Color(0, 0, 0));
	asteroid.setOutlineThickness(2);
	asteroid.setOutlineColor(sf::Color(250, 255, 255));
	asteroid.setPosition(position);
}

void Asteroid::randomVelocity()
{
	velocity.x = (float)std::rand() / RAND_MAX * 0.05;
	velocity.y = (float)std::rand() / RAND_MAX * 0.05;
}

void Asteroid::edges()
{
	const float height = 20;
	if (position.x > windowWidth / 2 + height)
	{
		position.x = -windowWidth / 2 - height;
	}
	else if (position.x < -windowWidth / 2 - height)
	{
		position.x = windowWidth / 2 + height;
	}
	else if (position.y > windowHeight / 2 + height)
	{
		position.y = -windowHeight / 2 - height;
	}
	else if (position.y < -windowHeight / 2 - height)
	{
		position.y = windowHeight / 2 + height;
	}
}