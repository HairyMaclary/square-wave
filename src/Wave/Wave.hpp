#pragma once

#include "Setup/Setup.h"
#include <list> // std::list

class Wave
{

private:
	std::vector<sf::Vertex> verticies;
	sf::RenderWindow& window;

	// Each vertex is one pixel. As a new vertex is added we need to shift right
	void shiftRight();

	// free up memory by removing those points that are off screen
	void removeOldValues();

public:
	Wave(sf::RenderWindow& window) :
		window { window }
	{}

	void addValue(float yValue);
	void update();
	void draw();
	sf::Vector2f getLastPosition()
	{
		sf::Vertex lastElement = verticies[verticies.size() - 1];
		return lastElement.position;
	}
};