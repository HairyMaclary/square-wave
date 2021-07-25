#include "./Laser.h"
#include "./Setup/Setup.h" // window dimensions eg windowWidt

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

// TODO: improve slow performance while firing
// one idea is to try transform with matricies.
// could also try removing delta time check on laser creation
// Another option is to set up the vectors in the asteroid object and
// just keep them around all the time but not draw them. Perhaps creating
// them is the casue of the lag.
// bool Laser::hitsAsteroid(Asteroid& asteroid)
// {
// 	return asteroid.hit(*this);
// const uint asteroidPointCount = asteroid.totalPoints;
// sf::FloatRect laserGlobalBounds = bolt.getGlobalBounds();

// // for each pair of neighbouring points around the asteroid make a vector.
// // Create new line shapes for each vector and check it's bounding box

// // for a collision
// for (uint i = 0; i < asteroidPointCount; i++)
// {
// 	sf::Vector2f firstPoint = asteroid.getPointTransform(i);
// 	// make sure we loop back to the zeroth value for the last section
// 	sf::Vector2f secondPoint = asteroid.getPointTransform((i + 1) % (asteroidPointCount));
// 	sf::Vector2f diffVec = secondPoint - firstPoint;
// 	// std::cout << "Laser. x: " << firstPoint.x << " y: " << firstPoint.y << std::endl;
// 	sf::RectangleShape perimeterSection(diffVec);

// 	float rotation = asteroid.asteroid.getRotation();
// 	sf::Vector2f scale = asteroid.asteroid.getScale();
// 	sf::Vector2f position(firstPoint);

// 	perimeterSection.setScale(scale);
// 	perimeterSection.setPosition(position);
// 	perimeterSection.setRotation(rotation);
// 	// window.draw(perimeterSection); // useful for debugging

// 	sf::FloatRect asteroidBounds = perimeterSection.getGlobalBounds();

// 	if (laserGlobalBounds.intersects(asteroidBounds))
// 	{
// 		return true;
// 	}
// }
// return false;
// }
