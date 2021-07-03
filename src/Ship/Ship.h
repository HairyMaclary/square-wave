#pragma once

class Ship
{
private:
	const float radius;
	sf::ConvexShape ship;
	sf::RenderWindow& window;
	float heading = 0;

public:
	Ship(sf::RenderWindow& mainWindow);
	void draw();
};