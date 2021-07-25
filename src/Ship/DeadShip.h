#pragma once

class DeadShip
{
private:
	sf::RenderWindow& window;
	sf::CircleShape ring;
	sf::Vector2f position;
	bool positionSet { false };
	float radius { 10.0f };
	float runningTime { 0.0f };
	float maxTime { 0.05f };
	bool reverse { false };
	bool finished { false };

public:
	DeadShip(sf::RenderWindow& renderWindow);
	void draw(float deltaTime, sf::Vector2f& shipPos);
};