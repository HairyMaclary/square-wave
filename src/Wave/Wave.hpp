#include "Setup/Setup.h"
#include <list> // std::list

class Wave
{

private:
	std::vector<sf::Vertex> verticies;
	sf::RenderWindow& window;

	// Each vertex is one pixel. As a new vertex is added we need to shift right
	void shiftRight()
	{
		std::vector<sf::Vertex>::iterator it;
		for (it = verticies.begin(); it != verticies.end(); ++it)
		{
			(*it).position.x += 1;
		}
	}

	// free up memory once for those points that are off screen
	void removeOldValues()
	{
		while (verticies.size() > window::width)
		{
			verticies.pop_back();
		}
	}

public:
	Wave(sf::RenderWindow& window) :
		window { window }
	{
	}

	void addValue(float yValue)
	{
		shiftRight();
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(0.f, yValue);
		vertex.color = sf::Color::White;
		verticies.push_back(vertex);
	}

	void update()
	{
		removeOldValues();
	}

	void draw()
	{
		window.draw(&verticies[0], verticies.size(), sf::Points);
	}
};