#include "./Laser.h"
#include "./Setup/Setup.h" // window dimensions eg windowWidt
#include <vector>		   // std::vector

const float pi = float(std::atan(1) * 4);

Laser::Laser(sf::RenderWindow& renderWindow, sf::Vector2f shipPos, float shipHeading) :
	window { renderWindow },
	position { shipPos }
{
	bolt.setSize(sf::Vector2f(3.0f, 10.0f));
	bolt.setOrigin(1.5f, 5.f);
	bolt.setRotation(shipHeading);
	bolt.setFillColor(sf::Color::White);
	velocityFromAngle(shipHeading);
}

void Laser::velocityFromAngle(float angle)
{
	const float speed = 0.5f;
	float vectorLength = std::sqrt(2 * speed * speed);
	float radians = angle * pi / 180.0f;
	velocity.x = vectorLength * std::sin(radians);
	velocity.y = vectorLength * -std::cos(radians);
}

void Laser::draw()
{
	position += velocity;
	bolt.setPosition(position);
	window.draw(bolt);
}

bool Laser::offscreen()
{
	if (
		position.x < -windowWidth / 2 || position.x > windowWidth / 2 || position.y < -windowHeight / 2 || position.y > windowHeight / 2)
	{
		return true;
	}
	return false;
}

// todo refactor. Don't need tow loops
bool Laser::hitsAsteroid(Asteroid& asteroid)
{
	const uint asteroidPointCount = asteroid.totalPoints;
	std::vector<sf::FloatRect> perimeterArray(asteroidPointCount);

	// make an array of 2D vectors that describe the perimerter of the asteroid
	for (uint i = 0; i < asteroidPointCount; i++)
	{
		sf::Vector2f firstPoint = asteroid.getPointTransform(i);
		// make sure we loop back to the zeroth value for the last section
		sf::Vector2f secondPoint = asteroid.getPointTransform((i + 1) % (asteroidPointCount));
		sf::Vector2f diffVec = firstPoint - secondPoint;
		sf::RectangleShape perimeterSection(diffVec);
		sf::FloatRect bounds = perimeterSection.getGlobalBounds();
		perimeterArray[i] = bounds;
	}

	for (uint i = 0; i < asteroidPointCount; i++)
	{
		sf::FloatRect laserGlobalBounds = bolt.getGlobalBounds();

		if (laserGlobalBounds.intersects(perimeterArray[i]))
		{
			return true;
		}
	}

	return false;
}

float Laser::distance(sf::Vector2f& p1, sf::Vector2f& p2)
{
	sf::Vector2f diffVec = p1 - p2;
	return std::sqrt(diffVec.x * diffVec.x + diffVec.y * diffVec.y);
}
