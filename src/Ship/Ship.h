#pragma once

class Ship
{
private:
	const float radius;
	sf::CircleShape ship;
	sf::RenderWindow& window;

public:
	Ship(sf::RenderWindow& mainWindow);
	void draw();
};