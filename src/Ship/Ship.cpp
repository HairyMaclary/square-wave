#include "./Ship.h"

Ship::Ship(sf::RenderWindow& mainWindow) :
	radius { 20.0f },
	window { mainWindow }
{
	ship.setPointCount(3);
	ship.setPoint(0, sf::Vector2f(0.f, 2 * -radius));
	ship.setPoint(1, sf::Vector2f(-radius / 2, -radius / 2));
	ship.setPoint(2, sf::Vector2f(radius / 2, -radius / 2));
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	ship.setOrigin(sf::Vector2f(radius, radius));
	ship.rotate(heading); // relative, otherwise use setRotation()
}

void Ship::draw()
{
	window.draw(ship);
}