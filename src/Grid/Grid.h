#include "Platform/Platform.hpp"
#include <vector>

class Grid
{
	int cols;
	int rows;
	float squareLength;
	sf::RenderWindow& mWindow;

private:
	bool** newGrid;
	std::vector<std::vector<sf::RectangleShape>> grid;
	std::vector<std::vector<sf::RectangleShape>> nextGrid;
	int getRandom();
	int getAliveNeighbors(int x, int y);
	bool isAlive(int i, int j);
	const sf::Color nextState(int i, int j);

public:
	Grid(float windowWidth, float windowHeight, int resolution, sf::RenderWindow& windowRef);
	~Grid();
	void draw();
};