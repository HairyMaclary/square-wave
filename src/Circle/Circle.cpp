#include "./Circle.hpp"
#include "../Setup/Setup.h"

Circle::Circle(sf::RenderWindow& window, uint iterationCount) :
	window { window }
{
	n = iterationCount * 2 + 1;
	radius = initalRadius * (4 / (n * constants::pi));

	circ.setRadius(radius);
	circ.setOutlineThickness(1.f);
	circ.setOutlineColor(sf::Color(255.f, 255.f, 255.f, 100.f));
	circ.setFillColor(sf::Color::Black);
	circ.setOrigin(radius, radius);
	circ.setPointCount(100);

	const float pointRadius = 6.f;
	point.setRadius(pointRadius);
	point.setOutlineThickness(1.f);
	point.setOutlineColor(sf::Color::White);
	point.setFillColor(sf::Color::White);
	point.setOrigin(pointRadius, pointRadius);

	line[0].position = sf::Vector2f(0.f, 0.f);
	line[1].position = sf::Vector2f(100.f, 100.f);
	line[0].color = sf::Color(255.f, 255.f, 255.f, 100.f);
	line[1].color = sf::Color(255.f, 255.f, 255.f, 100.f);
}

void Circle::update(float deltaTime)
{
	runningTime += deltaTime;
	if (runningTime > maxTime)
	{
		radians += 2 * constants::pi * maxTime * dampner;
		float x = radius * cos(radians);
		float y = radius * sin(radians);
		point.setPosition(x, y);
		runningTime = 0;
		line[1].position = sf::Vector2f(x, y);
	}
}

void Circle::draw()
{
	window.draw(circ);
	window.draw(point);
	window.draw(line);
}