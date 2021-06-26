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
		std::vector<state> column;
		column.resize(rows);
		for (int j { 0 }; j < rows; j++)
		{
			int state;
			int randomNum = getRandom();
			if (randomNum == 1)
			{
				state = false;
			}
			else
			{
				state = true;
			}
			column[j] = state;
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
			nextGrid[i][j] = nextState(i, j);
		}
	}

	grid = nextGrid;

	// Imrpove performance by moving constant properties out of the loop
	sf::RectangleShape square(sf::Vector2f(squareLength, squareLength));
	square.setOutlineThickness(-1);
	square.setOutlineColor(sf::Color(150, 150, 150));

	for (uint i { 0 }; i < grid.size(); i++)
	{
		for (uint j { 0 }; j < grid[i].size(); j++)
		{
			square.setPosition(i * squareLength, j * squareLength);

			int fillColor = grid[i][j] ? 0 : 255;
			square.setFillColor(sf::Color(fillColor, fillColor, fillColor));

			mWindow.draw(square);
		}
	}
}

int Grid::getRandom()
{
	return std::round((float)std::rand() / RAND_MAX);
}

bool Grid::isAlive(int i, int j)
{
	return grid[i][j];
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

state Grid::nextState(int i, int j)
{
	bool alive { isAlive(i, j) };

	int neighbours = getAliveNeighbors(i, j);

	if (alive && (neighbours == 2 || neighbours == 3))
	{
		return true;
	}
	else if (!alive && neighbours == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}
