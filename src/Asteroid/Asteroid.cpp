#include "./Asteroid.h"
#include "./Laser/Laser.h"
#include "Setup/Setup.h" /* windowWidth, windowHeight, pi */
#include <cmath>		 /* pow */
#include <math.h>		 /* sqrt */
#include <stdlib.h>		 /* srand, rand */
#include <time.h>		 /* time */

Asteroid::Asteroid(sf::RenderWindow& window, sf::Vector2f position, float radius) :
	window { window },
	position { position },
	localMaxRadius { radius }
{
	setUp();
}

Asteroid::Asteroid(sf::RenderWindow& window, sf::Vector2f& shipPos) :
	window { window },
	localMaxRadius { maxRadius }
{
	getRandomPosition(shipPos);
	setUp();
}

void Asteroid::getRandomPosition(sf::Vector2f shipPos)
{
	position.x = (float)std::rand() / RAND_MAX * window::width - (window::width / 2);
	position.y = (float)std::rand() / RAND_MAX * window::height - (window::height / 2);

	// Don't allow an asteroid to spawn too close to the ship
	float safeDistance = 100.0f;
	sf::Vector2f vecToShip(shipPos - position);
	float distance = sqrt(pow(vecToShip.y, 2) + pow(vecToShip.x, 2));
	while (distance < safeDistance)
	{
		position.x = (float)std::rand() / RAND_MAX * window::width - (window::width / 2);
		position.y = (float)std::rand() / RAND_MAX * window::height - (window::height / 2);
		vecToShip = shipPos - position;
		distance = sqrt(pow(vecToShip.y, 2) + pow(vecToShip.x, 2));
	}
}

void Asteroid::draw()
{
	edges();
	position += velocity;
	asteroid.setPosition(position.x, position.y);
	window.draw(asteroid);

	for (uint i = 0; i < totalPoints; i++)
	{
		sf::Vector2f pos = getPointTransform(i);
		boundaryLines[i].setPosition(pos.x, pos.y);
	}
}

void Asteroid::setUp()
{
	randomPointCount();
	makeAsteroid();
	makeCollisonBoundary();
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

	const float radiansPerPoint = 2 * constants::pi / totalPoints;
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

void Asteroid::makeCollisonBoundary()
{
	// The asteroids collision is large. So a series of lines are created
	// between adjancent verticies around the asteroid. These lines
	// are not drawn but instead are only used for collision detection.
	for (uint i = 0; i < totalPoints; i++)
	{
		sf::Vector2f firstPoint = getPointTransform(i);
		// make sure we loop back to the zeroth value for the last section
		sf::Vector2f secondPoint = getPointTransform((i + 1) % (totalPoints));
		sf::Vector2f diffVec = secondPoint - firstPoint;

		sf::RectangleShape perimeterSection(diffVec);

		float rotation = asteroid.getRotation();
		sf::Vector2f scale = asteroid.getScale();

		perimeterSection.setScale(scale);
		perimeterSection.setRotation(rotation);

		boundaryLines.emplace_back(perimeterSection);
	}
}

void Asteroid::randomVelocity()
{
	velocity.x = (float)std::rand() / RAND_MAX * 0.025;
	velocity.y = (float)std::rand() / RAND_MAX * 0.025;
}

void Asteroid::edges()
{
	const float height = 20;
	if (position.x > window::width / 2 + height)
	{
		position.x = -window::width / 2 - height;
	}
	else if (position.x < -window::width / 2 - height)
	{
		position.x = window::width / 2 + height;
	}
	else if (position.y > window::height / 2 + height)
	{
		position.y = -window::height / 2 - height;
	}
	else if (position.y < -window::height / 2 - height)
	{
		position.y = window::height / 2 + height;
	}
}

sf::Vector2f Asteroid::getPointTransform(uint pointIndex)
{
	sf::Vector2f localPoint = asteroid.getPoint(pointIndex);
	return asteroid.getTransform().transformPoint(localPoint);
}

sf::Vector2f Asteroid::getPosition()
{
	return position;
}

float Asteroid::getRadius()
{
	return localMaxRadius;
}


bool Asteroid::hit(const sf::FloatRect& bounds)
{
	// for performance we need a first pass with a simpler system
	// such comparing the radius of the longest point with the radisu of the ship
	// so that there is only once calculation.
	
	for (uint i = 0; i < totalPoints; i++)
	{
		sf::FloatRect segmentBounds = boundaryLines[i].getGlobalBounds();

		if (segmentBounds.intersects(bounds))
		{
			return true;
		}
	}

	return false;
}
