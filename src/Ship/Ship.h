#pragma once

class Ship
{
private:
	sf::ConvexShape ship;
	sf::RenderWindow& window;
	sf::Vector2f position { 0.0f, 0.0f };
	sf::Vector2f velocity { 0.0f, 0.0f };
	const float height;
	const float velocityDrag { 0.98f };
	const float maxTime { 1.0f / 60.0f }; // 60fps
	const float turnRate { 0.15f };
	const float inertia { 0.8f };
	float heading;
	float runningTime { 0 };
	bool boosting { false };

	void update(float deltaTime);
	void setPoints();
	void checkKeys();
	void edges();

public:
	Ship(sf::RenderWindow& mainWindow);
	void draw(float deltaTime);
	void turn(float angle);
	void boost();
	void reset();
};