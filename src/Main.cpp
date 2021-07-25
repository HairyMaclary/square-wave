#include "./Asteroid/Asteroid.h"
#include "./EventHandler/EventHandler.h"
#include "./Laser/Lasers.h"
#include "./Setup/Setup.h" // initial window dimensions and generateSetup()
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

	Lasers lasers(window, ship);

	std::vector<Asteroid*> asteroids;
	const uint initialAsteroidCount = 5;
	for (uint i = 0; i < initialAsteroidCount; ++i)
	{
		asteroids.emplace_back(new Asteroid(window));
	}

	// 	sf::Font font;
	// if (!font.loadFromFile("src/fonts/open-sans/OpenSans-Regular.ttf"))
	// {
	// 	sf::Font::Info info = font.getInfo();
	// 	std::cout << "Bugger, font load did not work" << info.family << std::endl;
	// }
	// const float distance = 100.0f;
	// sf::Text tl;
	// tl.setFont(font);
	// tl.setString("-ve -ve");
	// tl.setCharacterSize(24);
	// tl.setFillColor(sf::Color::Red);
	// tl.setPosition(-distance, -distance);

	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, ship);

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

		// TODO put all all asteroids in their own parent class.
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

		// window.draw(tl);
		ship.draw(deltaTime);
		window.display();
	}
	return 0;
}
