#include "../Setup/Setup.h"

class Circle
{
private:
	sf::RenderWindow& window;
	float initalRadius { 100 };
	uint n;
	float radius;
	sf::CircleShape circ;
	sf::CircleShape point;
	sf::VertexArray line { sf::Lines, 2 };
	float runningTime { 0 };
	const float maxTime { 0.0167 }; // 60 fps
	float radians { 0 };
	const float dampner { 0.1 };

public:
	Circle(sf::RenderWindow& window, uint iterationCount);
	void update(float deltaTime);
	void draw();
};