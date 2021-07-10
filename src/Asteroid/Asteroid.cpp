#include "./Asteroid.h"
#include "Setup/Setup.h" /* windowWidth, windowHeight */
#include <stdlib.h>		 /* srand, rand */
#include <time.h>		 /* time */

void Asteroid::getRandomRadius()
{
	radius = (float)std::rand() / RAND_MAX * maxRadius;
}

void Asteroid::getRandomPosition()
{
	position.x = (float)std::rand() / RAND_MAX * windowWidth - (windowWidth / 2);
	position.y = (float)std::rand() / RAND_MAX * windowHeight - (windowHeight / 2);
}

Asteroid::Asteroid(sf::Vector2f position, float radius) :
	position { position },
	radius { radius }
{
	srand(time(0));
	
}

Asteroid::Asteroid()
{
	srand(time(0));
	getRandomPosition();
	getRandomRadius();
}
