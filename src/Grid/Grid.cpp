#include "Grid.h"
#include "Platform/Platform.hpp"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>

Grid::Grid(float windowWidth, float windowHeight, int resolution, sf::RenderWindow& windowRef) :
	mWindow { windowRef }
{
	srand(time(0));
	if (windowWidth > windowHeight)
	{
		this->squareLength = windowWidth / resolution;
	}
	else
	{
		this->squareLength = windowHeight / resolution;
	}

	this->cols = (int)(windowWidth / squareLength);
	this->rows = (int)(windowHeight / squareLength);

	// this->newGrid = new bool*[cols];
	// for (int c = 0; c < cols; c++)
	// {
	// 	newGrid[c] = new bool[rows];
	// }

	grid.resize(cols);

	for (int i { 0 }; i < cols; i++)
	{
		std::vector<sf::RectangleShape> column;
		column.resize(rows);
		for (int j { 0 }; j < rows; j++)
		{
			// Move non-const (position/fill) to draw call
			// Move const (size, outline) out of loop
			sf::RectangleShape square(sf::Vector2f(squareLength, squareLength));
			square.setPosition(i * squareLength, j * squareLength);
			int fill;
			int randomNum = getRandom();
			if (randomNum == 1)
			{
				fill = 255;
			}
			else
			{
				fill = 0;
			}
			square.setOutlineThickness(-1);
			square.setFillColor(sf::Color(fill, fill, fill));
			square.setOutlineColor(sf::Color(150, 150, 150));
			column[j] = square;
		}
		grid[i] = column;
	}
	nextGrid = grid;
}

// once you've used the new keyword you'll be wanting a deconstructor.
Grid::~Grid()
{
	// delete in reverse order to creation.

	// for (int c = 0; c < cols; c++)
	// {
	// 	delete[] newGrid[c];
	// }
	// delete[] newGrid;
}

void Grid::draw()
{
	for (int i { 0 }; i < cols; i++)
	{
		for (int j { 0 }; j < rows; j++)
		{
			const sf::Color& next = nextState(i, j);
			nextGrid[i][j].setFillColor(next);
		}
	}

	grid = nextGrid;

	for (uint i { 0 }; i < grid.size(); i++)
	{
		for (uint j { 0 }; j < grid[i].size(); j++)
		{
			mWindow.draw(grid[i][j]);
		}
	}
}

int Grid::getRandom()
{
	return std::round((float)std::rand() / RAND_MAX);
}

bool Grid::isAlive(int i, int j)
{
	const sf::Color& color = grid[i][j].getFillColor();
	if (color.r == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Grid::getAliveNeighbors(int x, int y)
{
	int sum { 0 };
	for (int i { -1 }; i < 2; i++)
	{
		for (int j { -1 }; j < 2; j++)
		{
			int col { (x + i + cols) % cols };
			int row { (y + j + rows) % rows };
			sum += isAlive(col, row);
		}
	}

	sum -= isAlive(x, y);
	return sum;
}

const sf::Color Grid::nextState(int i, int j)
{
	bool alive { isAlive(i, j) };

	// TODO ditch curly braces and signed ints
	// only expect curly braces when initializing an array
	int neighbours { getAliveNeighbors(i, j) };

	if (alive && (neighbours == 2 || neighbours == 3))
	{
		return sf::Color(0, 0, 0);
	}
	else if (!alive && neighbours == 3)
	{
		return sf::Color(0, 0, 0);
	}
	else
	{
		return sf::Color(255, 255, 255);
	}
}
