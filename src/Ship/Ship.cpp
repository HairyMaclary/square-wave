#include "./Ship.h"
#include "./Setup/Setup.h"
#include <iostream>
#include <math.h>

const float pi = float(std::atan(1) * 4);

Ship::Ship(sf::RenderWindow& mainWindow) :
	height { 20.0f },
	window { mainWindow },
	heading { 0 }
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
	// velocity is not frame or machine specific
	runningTime += deltaTime;
	checkKeys();
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
