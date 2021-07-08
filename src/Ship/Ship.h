#pragma once

class Ship
{
private:
	const float height;
	sf::ConvexShape ship;
	// sf::CircleShape ship { 20.0f, 3 };
	sf::RenderWindow& window;
	float heading;
	sf::Vector2f position { 0.0f, 0.0f };
	sf::Vector2f velocity { 0.0f, 0.0f };

	void update();
	void setPoints();

public:
	Ship(sf::RenderWindow& mainWindow);
	void draw();
	void turn(float angle);
	void boost();
};