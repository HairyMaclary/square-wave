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

Asteroid::Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius) :
	window { window },
	position { position },
	localMaxRadius { radius }
{
	setUp();
}

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
	position += velocity;
	asteroid.setPosition(position.x, position.y);

	window.draw(asteroid);
}

void Asteroid::setUp()
{
	randomPointCount();
	makeAsteroid();
	randomVelocity();
}

void Asteroid::randomPointCount()
{
	const uint maxBasePoints = 20;
	const uint minPoints = 10; // will given a max of 20 points
	totalPoints = std::round((float)std::rand() / RAND_MAX * maxBasePoints) + minPoints;
}

void Asteroid::makeAsteroid()
{
	asteroid.setPointCount(totalPoints);

	const float radiansPerPoint = 2 * pi / totalPoints;
	float pointDistance = localMaxRadius;

	for (uint i = 0; i < totalPoints; i++)
	{
		const float angle = (i + 1) * radiansPerPoint;
		float lengthVariationCoef = ((float)std::rand() / RAND_MAX) * 0.4 + 0.8;
		pointDistance = pointDistance * lengthVariationCoef;
		const float xPos = pointDistance * std::sin(angle);
		const float yPos = pointDistance * -std::cos(angle);
		sf::Vector2f relativeVector(xPos, yPos);
		asteroid.setPoint(i, relativeVector);
	}
	asteroid.setFillColor(sf::Color(0, 0, 0));
	asteroid.setOutlineThickness(2);
	asteroid.setOutlineColor(sf::Color(250, 255, 255));
	asteroid.setPosition(position);
}

void Asteroid::randomVelocity()
{
	velocity.x = (float)std::rand() / RAND_MAX * 0.01;
	velocity.y = (float)std::rand() / RAND_MAX * 0.01;
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

sf::Vector2f Asteroid::getPointTransform(uint pointIndex)
{
	sf::Vector2f localPoint = asteroid.getPoint(pointIndex);
	return asteroid.getTransform().transformPoint(localPoint);
}
