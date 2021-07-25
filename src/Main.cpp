#include "./Asteroid/Asteroid.h"
#include "./EventHandler/EventHandler.h"
#include "./Laser/Lasers.h"
#include "./Score/Score.h"
#include "./Setup/Setup.h" // initial window dimensions and generateSetup()
#include "./Ship/DeadShip.h"
#include "./Ship/Ship.h"
#include <iostream>
#include <vector> // std::vector

main()
{
	// move this to the asteroids class when it is created.
	srand(time(0));

	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view);

	Ship ship(window);
	DeadShip deadShip(window);

	Lasers lasers(window, ship);

	std::vector<Asteroid*> asteroids;
	const uint initialAsteroidCount = 5;
	for (uint i = 0; i < initialAsteroidCount; ++i)
	{
		asteroids.emplace_back(new Asteroid(window, ship.position));
	}

	Score score(window);

	float deltaTime = 0.0f;
	float runningTime = 0.0f;
	float spawnTime = 10.0f;

	sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, ship, view);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			handler.process(event);
		}

		window.clear(sf::Color(0, 0, 0));
		window.setView(view);

		lasers.draw(deltaTime);

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

		if (!ship.alive)
		{
			deadShip.draw(deltaTime, ship.position);
		}

		score.draw();
		ship.draw(deltaTime);
		window.display();
	}
	return 0;
}
