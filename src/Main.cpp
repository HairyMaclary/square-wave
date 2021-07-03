#include "./EventHandler/EventHandler.h"
#include "./Setup/Setup.h" // initial window dimensions and generateSetup()
#include "./Ship/Ship.h"
#include <iostream>

main()
{
	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view);

	Ship ship(window);

	// float deltaTime = 0.0f;

	// sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, view);

	while (window.isOpen())
	{
		// deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			handler.process(event);
		}

		window.clear(sf::Color(0, 0, 0));
		ship.draw();
		window.setView(view);
		window.display();
	}

	return 0;
}
