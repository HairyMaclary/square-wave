#include "./Laser.h"
#include "./Setup/Setup.h" // window dimensions eg windowWidth, and pi

Laser::Laser(sf::RenderWindow& renderWindow, sf::Vector2f shipPos, float shipHeading) :
	window { renderWindow },
	position { shipPos }
{
	bolt.setSize(sf::Vector2f(3.0f, boltLength));
	bolt.setOrigin(1.5f, 5.f);
	bolt.setRotation(shipHeading);
	bolt.setFillColor(sf::Color::White);
	velocityFromAngle(shipHeading);
}

void Laser::velocityFromAngle(float angle)
{
	const float speed = 0.5f;
	float vectorLength = std::sqrt(2 * speed * speed);
	float radians = angle * constants::pi / 180.0f;
	velocity.x = vectorLength * std::sin(radians);
	velocity.y = vectorLength * -std::cos(radians);
}

void Laser::update()
{
	position += velocity;
	bolt.setPosition(position);
}

void Laser::draw()
{
	update();
	window.draw(bolt);
}

bool Laser::offscreen()
{
	if (
		position.x < -window::width / 2 || position.x > window::width / 2 || position.y < -window::height / 2 || position.y > window::height / 2)
	{
		return true;
	}
	return false;
}

sf::FloatRect Laser::getGlobalBounds()
{
	return bolt.getGlobalBounds();
}

sf::Vector2f Laser::getPosition()
{
	return bolt.getPosition();
}

float Laser::getBoltLength()
{
	return boltLength;
}