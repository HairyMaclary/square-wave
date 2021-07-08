#include "./Ship.h"
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
	// TODO: get back into the video and the get the physic multipliers sorted out.
}

void Ship::draw()
{
	ship.setRotation(heading);
	update();
	window.draw(ship);
}

void Ship::turn(float angle)
{
	heading += angle;
}

void Ship::update()
{
	position.x += velocity.x;
	position.y += velocity.y;

	velocity.x *= 0.7;
	velocity.y *= 0.7;

	ship.setPosition(position.x, position.y);
}

void Ship::boost()
{
	float vectorLength = std::sqrt(2);
	float radians = heading * pi / 180.0f;
	float xForce = vectorLength * std::sin(radians);
	float yForce = vectorLength * -std::cos(radians);

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