#pragma once

class Circle
{
private:
	sf::RenderWindow& window;
	float initalRadius { 100 };
	uint n;
	float radius;
	sf::CircleShape circ;
	sf::CircleShape point;
	sf::VertexArray line { sf::Lines, 2 };
	float radians;
	const float dampner { 0.1 };

public:
	Circle(sf::RenderWindow& window, uint iterationCount, float radians = 0);
	void update(float& x, float& y);
	void draw();
	float getRadians();
};