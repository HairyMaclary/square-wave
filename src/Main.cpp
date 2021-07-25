#include "./Asteroid/Asteroids.h"
#include "./EventHandler/EventHandler.h"
#include "./Laser/Lasers.h"
#include "./Score/Score.h"
#include "./Setup/Setup.h" // initial window dimensions and generateSetup()
#include "./Ship/DeadShip.h"
#include "./Ship/Ship.h"

main()
{
	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view);

	Ship ship(window);
	DeadShip deadShip(window);
	Lasers lasers(window, ship);
	Score score(window);
	Asteroids asteroids(window, ship, lasers, score);

	float deltaTime = 0.0f;
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
		asteroids.draw(deltaTime);
		ship.draw(deltaTime);

		if (!ship.alive)
		{
			deadShip.draw(deltaTime, ship.position);
		}

		score.draw();
		window.display();
	}
	return 0;
}
