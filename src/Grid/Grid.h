#include "Platform/Platform.hpp"
#include <vector>

using state = bool;

class Grid
{
	int cols;
	int rows;
	float squareLength;
	sf::RenderWindow& mWindow;

private:
	bool** newGrid;
	std::vector<std::vector<state>> grid;
	std::vector<std::vector<state>> nextGrid;
	int getRandom();
	int getAliveNeighbors(int x, int y);
	bool isAlive(int i, int j);
	state nextState(int i, int j);

public:
	Grid(float windowWidth, float windowHeight, int resolution, sf::RenderWindow& windowRef);
	~Grid();
	void draw();
};