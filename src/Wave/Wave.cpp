#include "Wave.hpp"

void Wave::shiftRight()
{
	std::vector<sf::Vertex>::iterator it;
	for (it = verticies.begin(); it != verticies.end(); ++it)
	{
		(*it).position.x += 1;
	}
}

void Wave::removeOldValues()
{
	while (verticies.size() > window::width)
	{
		verticies.pop_back();
	}
}

void Wave::addValue(float yValue)
{
	shiftRight();
	sf::Vertex vertex;
	vertex.position = sf::Vector2f(300.f, yValue);
	vertex.color = sf::Color::White;
	verticies.push_back(vertex);
}

void Wave::update()
{
	removeOldValues();
}

void Wave::draw()
{
	window.draw(&verticies[0], verticies.size(), sf::Points);
}