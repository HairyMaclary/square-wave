#include "./Ship.h"

Ship::Ship(sf::RenderWindow& mainWindow) :
	radius { 20.0f },
	window { mainWindow }
{
	ship.setPointCount(3);
	ship.setPoint(0, sf::Vector2f(0.f, -radius));
	ship.setPoint(1, sf::Vector2f(-radius / 2, radius / 2));
	ship.setPoint(2, sf::Vector2f(radius / 2, radius / 2));
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	ship.rotate(heading); // relative, otherwise use setRotation()
}

void Ship::draw()
{
	turn(0.5f);
	ship.rotate(heading);
	window.draw(ship);
}

void Ship::turn(float angle)
{
	heading += angle;
}