#include "./Asteroids.h"
#include "../src/Asteroid/Asteroid.h"
#include "../src/Laser/Lasers.h"
#include "../src/Ship/Ship.h"

Asteroids::Asteroids(sf::RenderWindow& renderwindow, Ship& ship, Lasers& lasers, Score& score) :
	window { renderwindow },
	ship { ship },
	lasers { lasers },
	score { score }
{
	srand(time(0));

	for (uint i = 0; i < initialAsteroidCount; ++i)
	{
		asteroids.emplace_back(new Asteroid(window, ship.position));
	}
}

void Asteroids::draw(float deltaTime)
{
	std::vector<Asteroid*>::iterator position = asteroids.begin();

	for (uint i = 0; i < asteroids.size(); i++)
	{
		const bool hit = lasers.hits(*asteroids[i]);
		if (hit)
		{
			auto radius = (*position)->getRadius();
			auto pos = (*position)->getPosition();

			delete (*position);
			(*position) = nullptr;
			asteroids.erase(position);

			score.update(radius);

			if (radius > 5)
			{
				asteroids.emplace_back(new Asteroid(window, pos, radius / 2));
				asteroids.emplace_back(new Asteroid(window, pos, radius / 2));
			}
		}
		else
		{
			++position;
			(*asteroids[i]).draw();
			ship.hits(*asteroids[i]);
		}
	}

	runningTime += deltaTime;
	if (ship.alive && runningTime > spawnTime)
	{
		runningTime = 0;
		spawnTime *= 0.95f;
		// prevent late game 'avalanche' of asteroids
		if (spawnTime < 3)
		{
			spawnTime = 10.0f;
		}
		asteroids.emplace_back(new Asteroid(window, ship.position));
	}
}