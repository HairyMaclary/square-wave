#include "./Ship.h"
#include "./Asteroid/Asteroid.h"
#include "./Setup/Setup.h" // window dimensions eg windowWidth
#include <iostream>
#include <math.h>

//TODO central location for this. Also used in asteroid and laser.
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

	if (!soundBuffer.loadFromFile("src/sounds/explosion.wav"))
	{
		std::cout << "Bugger, sound load did not work" << std::endl;
	}

	destructionSound.setBuffer(soundBuffer);
}

void Ship::draw(float deltaTime)
{

	ship.setRotation(heading);
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
		const sf::FloatRect& bounds = ship.getGlobalBounds();

		if (asteroid.hit(bounds))
		{
			alive = false;
			destructionSound.play();
			return;
		}
	}
}

sf::FloatRect Ship::getGlobalBounds()
{
	return ship.getGlobalBounds();
}
