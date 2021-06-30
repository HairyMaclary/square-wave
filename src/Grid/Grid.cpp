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

	this->cols = (uint)(windowWidth / squareLength);
	this->rows = (uint)(windowHeight / squareLength);

	this->grid = new bool*[cols];
	this->nextGrid = new bool*[cols];
	for (uint c = 0; c < cols; c++)
	{
		grid[c] = new bool[rows];
		nextGrid[c] = new bool[rows];
	}

	for (uint i { 0 }; i < cols; i++)
	{
		for (uint j { 0 }; j < rows; j++)
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
			grid[i][j] = state;
			nextGrid[i][j] = state;
		}
	}
}

// once you've used the 'new' keyword you'll be wanting a deconstructor.
Grid::~Grid()
{
	// delete in reverse order to creation.
	for (uint c = 0; c < cols; c++)
	{
		delete[] grid[c];
		delete[] nextGrid[c];
	}
	delete[] grid;
	delete[] nextGrid;
}

void Grid::draw()
{
	for (uint i { 0 }; i < cols; i++)
	{
		for (uint j { 0 }; j < rows; j++)
		{
			nextGrid[i][j] = nextState(i, j);
		}
	}

	for (uint x = 0; x < cols; x++)
	{
		for (uint y = 0; y < rows; y++)
		{
			grid[x][y] = nextGrid[x][y];
		}
	}

	// Improve performance by moving fixed properties out of the loop
	sf::RectangleShape square(sf::Vector2f(squareLength, squareLength));
	square.setOutlineThickness(-1);
	square.setOutlineColor(sf::Color(150, 150, 150));

	for (uint i { 0 }; i < cols; i++)
	{
		for (uint j { 0 }; j < rows; j++)
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
			uint col { (x + i + cols) % cols };
			uint row { (y + j + rows) % rows };
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
