#pragma once

#include "../src/Asteroid/Asteroid.h"
#include "../src/Laser/Lasers.h"
#include "../src/Score/Score.h"
#include "../src/Ship/Ship.h"
#include <list> // std::list

class Asteroids
{
private:
	sf::RenderWindow& window;
	Ship& ship;
	Lasers& lasers;
	Score& score;
	std::list<Asteroid*> asteroids;
	uint initialAsteroidCount { 5 };
	float runningTime = 0.0f;
	float spawnTime = 10.0f;

	void update(float deltaTime);

public:
	Asteroids(sf::RenderWindow& renderwindow, Ship& ship, Lasers& Lasers, Score& score);
	void draw(float deltaTime);
};