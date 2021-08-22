#include "./Circle.hpp"
#include "../Setup/Setup.h"

Circle::Circle(sf::RenderWindow& window, uint iterationCount, float radians) :
	window { window },
	radians { radians }
{
	n = iterationCount * 2 + 1;
	radius = initalRadius * (4 / (n * constants::pi));

	circ.setRadius(radius);
	circ.setOutlineThickness(1.f);
	circ.setOutlineColor(sf::Color(255.f, 255.f, 255.f, 100.f));
	circ.setFillColor(sf::Color::Transparent);
	circ.setOrigin(radius, radius);
	circ.setPointCount(100);

	const float pointRadius = 3.f;
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

void Circle::update(float& x, float& y)
{
	circ.setPosition(x, y);
	line[0].position = sf::Vector2f(x, y);

	radians += 2 * constants::pi * constants::maxTime * dampner;
	x += radius * cos(n * radians);
	y += radius * sin(n * radians);
	point.setPosition(x, y);
	line[1].position = sf::Vector2f(x, y);
}

void Circle::draw()
{
	window.draw(circ);
	window.draw(point);
	window.draw(line);
}

float Circle::getRadians()
{
	return radians;
}