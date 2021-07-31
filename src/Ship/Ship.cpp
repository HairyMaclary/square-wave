#include "./Ship.h"
#include "./Asteroid/Asteroid.h"
#include "./Setup/Setup.h" // window dimensions eg windowWidth
#include <iostream>
#include <math.h>

Ship::Ship(sf::RenderWindow& mainWindow) :
	window { mainWindow }
{
	ship.setPointCount(pointCount);
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	setPoints();
	makeCollisonBoundary();

	if (!soundBuffer.loadFromFile("src/sounds/explosion.wav"))
	{
		std::cout << "Bugger, sound load did not work" << std::endl;
	}

	destructionSound.setBuffer(soundBuffer);
}

void Ship::draw(float deltaTime)
{
	update(deltaTime);
	if (alive)
	{
		window.draw(ship);
	}
}

void Ship::turn(float angle)
{
	heading += angle;
}

void Ship::update(float deltaTime)
{
	ship.setRotation(heading);
	checkKeys();
	if (!alive)
	{
		return;
	}
	runningTime += deltaTime;

	if (runningTime > maxTime)
	{
		runningTime = 0;
		if (boosting)
		{
			boost();
		}
		edges();
		velocity.x *= velocityDrag;
		velocity.y *= velocityDrag;
		position.x += velocity.x;
		position.y += velocity.y;

		ship.setPosition(position.x, position.y);

		for (uint i = 0; i < pointCount; i++)
		{
			sf::Vector2f pos = getPointTransform(i);
			boundaryLines[i].setPosition(pos.x, pos.y);
		}
	}
}

void Ship::boost()
{
	float vectorLength = std::sqrt(2);
	float radians = heading * constants::pi / 180.0f;
	float xForce = vectorLength * std::sin(radians) * inertia;
	float yForce = vectorLength * -std::cos(radians) * inertia;

	velocity.x += xForce;
	velocity.y += yForce;
}

void Ship::setPoints()
{
	const float width = height / 2; // shorter 'sides' so that the 'front' is more obvious
	sf::Vector2f nosePoint(position.x, position.y - height);
	sf::Vector2f portPoint(position.x - width, position.y + width);
	sf::Vector2f starboardPoint(position.x + width, position.y + width);

	ship.setPoint(0, nosePoint);
	ship.setPoint(1, portPoint);
	ship.setPoint(2, starboardPoint);
}

void Ship::reset()
{
	velocity.x = 0;
	velocity.y = 0;
	position.x = 0;
	position.y = 0;
	heading = 0;
	alive = true;
	ship.setPosition(position.x, position.y);
}

void Ship::checkKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		turn(turnRate);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		turn(-turnRate);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		boosting = true;
	}
	else
	{
		boosting = false;
	}

	// for testing only
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	// {
	// 	reset();
	// }
}

// since this is used more than once in two different objects
// we should pull this out into a view management function or
// possibly a class (not call it 'utility' because it will get lost)
// It would take in a position (and height) and return the new position.
// Have a namespace in an .hpp file that wraps this up.
void Ship::edges()
{
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

// should be pulled out into a geometry or math file, and inside a namespace.
float Ship::distance(sf::Vector2f& p1, sf::Vector2f& p2)
{
	sf::Vector2f diffVec = p1 - p2;
	return std::sqrt(diffVec.x * diffVec.x + diffVec.y * diffVec.y);
}

// This interaction needs to be tested in a 3rd party class/namespace.
// This should then return a boolean. The function is currently doing two jobs.
// What if there was more logic to do once a hit was detected? Eg, hit points.
// It should not be the job of the utility function to know what should happen
// once a hit is detected. This is a common problem in programming.
// Make a pure function to make it reusable. This also spearates state better,
// and helps with debugging.
void Ship::hits(Asteroid& asteroid)
{
	if (alive)
	{
		sf::Vector2f asteroidPos = asteroid.getPosition();
		sf::Vector2f shipPos = ship.getPosition();
		sf::Vector2f diffVec = shipPos - asteroidPos;
		float distance = sqrt(diffVec.x * diffVec.x + diffVec.y * diffVec.y);
		float asteroidRadius = asteroid.getRadius();
		// once the the ship is approximatley within 20px of the asteroid
		// then use fine grained collision detection.
		const bool isNearby = distance < asteroidRadius + height + 20;
		if (isNearby)
		{
			for (uint i = 0; i < pointCount; i++)
			{
				const sf::FloatRect& bounds = boundaryLines[i].getGlobalBounds();

				if (asteroid.hit(bounds))
				{
					alive = false;
					destructionSound.play();
					return;
				}
			}
		}
	}
}

void Ship::makeCollisonBoundary()
{
	// A group of lines around the ship to better test for collisons
	for (uint i = 0; i < pointCount; i++)
	{
		sf::Vector2f firstPoint = getPointTransform(i);
		// make sure we loop back to the zeroth value for the last section
		sf::Vector2f secondPoint = getPointTransform((i + 1) % (pointCount));
		sf::Vector2f diffVec = secondPoint - firstPoint;

		sf::RectangleShape perimeterSection(diffVec);

		float rotation = ship.getRotation();
		sf::Vector2f scale = ship.getScale();

		perimeterSection.setScale(scale);
		perimeterSection.setRotation(rotation);

		boundaryLines.emplace_back(perimeterSection);
	}
}

sf::Vector2f Ship::getPointTransform(uint pointIndex)
{
	sf::Vector2f localPoint = ship.getPoint(pointIndex);
	return ship.getTransform().transformPoint(localPoint);
}
