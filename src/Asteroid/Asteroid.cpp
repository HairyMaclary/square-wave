#include "./Asteroid.h"
#include "Setup/Setup.h" /* windowWidth, windowHeight */
#include <stdlib.h>		 /* srand, rand */
#include <time.h>		 /* time */

//TODO central location for this. Also used in ship.cpp.
// Possibly even consinder extending sf::vector with p5 like functionality.
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
	window.draw(asteroid);
}

void Asteroid::setUp()
{
	srand(time(0));
	getTotalPointCount();
	makeAsteroid();
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
		const float pointDistance = (float)std::rand() / RAND_MAX * localMaxRadius;
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
