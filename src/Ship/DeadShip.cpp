#include "./DeadShip.h"
#include <optional>

DeadShip::DeadShip(sf::RenderWindow& renderWindow) :
	window { renderWindow }
{
	ring.setRadius(radius);
	ring.setOrigin(radius / 2, radius / 2);
	ring.setPointCount(100);
	ring.setOutlineThickness(2);
	ring.setOutlineColor(sf::Color::Red);
	ring.setFillColor(sf::Color::Black);
}

void DeadShip::draw(float deltaTime, sf::Vector2f& shipPos)
{
	if (!positionSet)
	{
		position = shipPos;
		positionSet = true;
	}
	runningTime += deltaTime;

	if (runningTime > maxTime)
	{
		if (!reverse && radius < 55)
		{
			radius += 1;
			runningTime = 0;
		}
		else if (!reverse && radius >= 55)
		{
			reverse = true;
		}
		else if (reverse && radius > 0)
		{
			radius -= 1;

			runningTime = 0;
		}
		else
		{
			finished = true;
		}
	}
	if (!finished)
	{
		ring.setOrigin(radius / 2, radius / 2);
		ring.setPosition(position);
		ring.setRadius(radius);
		window.draw(ring);
	}
}