#include "./Asteroid.h"
#include "./Laser/Laser.h"
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

	for (uint i = 0; i < totalPoints; i++)
	{
		sf::Vector2f pos = getPointTransform(i);
		boundaryLines[i].setPosition(pos.x, pos.y);
		// window.draw(boundaryLines[i]);
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

void Asteroid::makeCollisonBoundary()
{
	// Creating a set of verticies around the asteroid.
	// Not creating a normal sf::shape because we want a finer control over hit-boxes.
	// Instead we have a group of vectors constructed between adjacent points.
	for (uint i = 0; i < totalPoints; i++)
	{
		sf::Vector2f firstPoint = getPointTransform(i);
		// make sure we loop back to the zeroth value for the last section
		sf::Vector2f secondPoint = getPointTransform((i + 1) % (totalPoints));
		sf::Vector2f diffVec = secondPoint - firstPoint;

		boundaryPoints.emplace_back(new sf::Vector2f(diffVec.x, diffVec.y));

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

sf::Vector2f Asteroid::getPosition()
{
	return position;
}

float Asteroid::getRadius()
{
	return localMaxRadius;
}

// template <typename T>
bool Asteroid::hit(Laser& obj)
{
	sf::FloatRect objGlobalBounds = obj.bolt.getGlobalBounds();
	for (uint i = 0; i < totalPoints; i++)
	{
		sf::FloatRect segmentBounds = boundaryLines[i].getGlobalBounds();

		if (segmentBounds.intersects(objGlobalBounds))
		{
			return true;
		}
	}

	return false;
}