#pragma once

class Laser
{
private:
	sf::RenderWindow& window;
	float boltLength { 10.0f };
	sf::RectangleShape bolt;
	sf::Vector2f position;
	sf::Vector2f velocity;
	void update();

	void velocityFromAngle(float angle);

public:
	Laser(
		sf::RenderWindow& renderWindow,
		sf::Vector2f shipPos,
		float shipHeading);
	void draw();
	bool offscreen();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	float getBoltLength();
};