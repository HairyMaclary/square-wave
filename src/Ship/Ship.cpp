#include "./Ship.h"
#include "./Asteroid/Asteroid.h"
#include "./Setup/Setup.h"
#include <iostream>
#include <math.h>

//TODO central location for this. Also used in asteroid.
// Possibly even consider extending sf::vector with p5 like functionality.
const float pi = float(std::atan(1) * 4);

Ship::Ship(sf::RenderWindow& mainWindow) :
	window { mainWindow }
{
	ship.setPointCount(3);
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	setPoints();
	// ship.setOrigin(10.0f, 10.0f);

	//TODO, get the origin sorted out so that collisions and lasers bolts will line up
}

void Ship::draw(float deltaTime)
{
	ship.setRotation(heading);
	update(deltaTime);
	window.draw(ship);
}

void Ship::turn(float angle)
{
	heading += angle;
}

void Ship::update(float deltaTime)
{
	checkKeys();
	if (!alive)
	{
		return;
	}
	// velocity is not frame or machine specific
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
	}
}

void Ship::boost()
{
	float vectorLength = std::sqrt(2);
	float radians = heading * pi / 180.0f;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		reset();
	}
}

void Ship::edges()
{
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

float Ship::distance(sf::Vector2f& p1, sf::Vector2f& p2)
{
	sf::Vector2f diffVec = p1 - p2;
	return std::sqrt(diffVec.x * diffVec.x + diffVec.y * diffVec.y);
}

void Ship::hits(Asteroid& asteroid)
{
	if (alive)
	{
		const uint asteroidPointCount = asteroid.totalPoints;

		for (uint i = 0; i < asteroidPointCount; i++)
		{
			sf::Vector2f asteroidPointGlobal = asteroid.getPointTransform(i);

			for (uint j = 0; j < 3; j++)
			{
				sf::Vector2f shipPointLocal = ship.getPoint(i);
				sf::Vector2f shipPointGlobal = ship.getTransform().transformPoint(shipPointLocal);
				const float dist = distance(asteroidPointGlobal, shipPointGlobal);
				// Don't know why this fudge factor is needed. Points not lining up?
				const float ohFudge = 20.0f;
				if (dist <= ohFudge)
				{
					alive = false;
					return;
				}
			}
		}
	}
}
