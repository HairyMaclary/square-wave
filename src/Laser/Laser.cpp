#include "./Laser.h"

const float pi = float(std::atan(1) * 4);

Laser::Laser(sf::RenderWindow& window, sf::Vector2f shipPos, float shipHeading) :
	window { window },
	position { shipPos }
{
	std::cout << shipPos.x << shipPos.y << shipHeading << std::endl;
	bolt.setSize(sf::Vector2f(3.0f, 10.0f));
	bolt.setOrigin(1.5f, 5.f);
	bolt.setRotation(shipHeading);
	bolt.setFillColor(sf::Color::White);
	velocityFromAngle(shipHeading);
}

void Laser::velocityFromAngle(float angle)
{
	const float speed = 0.05f;
	float vectorLength = std::sqrt(2 * speed * speed);
	float radians = angle * pi / 180.0f;
	velocity.x = vectorLength * std::sin(radians);
	velocity.y = vectorLength * -std::cos(radians);
}

void Laser::draw()
{
	position += velocity;
	bolt.setPosition(position);
	window.draw(bolt);
}