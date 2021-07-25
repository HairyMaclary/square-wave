#include "./Laser.h"
#include "./Setup/Setup.h" // window dimensions eg windowWidt

const float pi = float(std::atan(1) * 4);

Laser::Laser(sf::RenderWindow& renderWindow, sf::Vector2f shipPos, float shipHeading) :
	window { renderWindow },
	position { shipPos }
{
	bolt.setSize(sf::Vector2f(3.0f, 10.0f));
	bolt.setOrigin(1.5f, 5.f);
	bolt.setRotation(shipHeading);
	bolt.setFillColor(sf::Color::White);
	velocityFromAngle(shipHeading);
}

void Laser::velocityFromAngle(float angle)
{
	const float speed = 0.5f;
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

bool Laser::offscreen()
{
	if (
		position.x < -windowWidth / 2 || position.x > windowWidth / 2 || position.y < -windowHeight / 2 || position.y > windowHeight / 2)
	{
		return true;
	}
	return false;
}

sf::FloatRect Laser::getGlobalBounds()
{
	return bolt.getGlobalBounds();
}