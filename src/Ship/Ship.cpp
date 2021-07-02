#include "./Ship.h"

Ship::Ship(sf::RenderWindow& mainWindow) :
	radius { 40.0f },
	window { mainWindow }
{
	ship.setRadius(radius);
	ship.setPointCount(3);
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	ship.setOrigin(sf::Vector2f(radius, radius));
}

void Ship::draw()
{
	window.draw(ship);
}