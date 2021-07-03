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
	EventHandler handler(window);

	while (window.isOpen())
	{
		// deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			handler.process(event);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			ship.turn(0.2f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			ship.turn(-0.2f);
		}

		window.clear(sf::Color(0, 0, 0));
		ship.draw();
		window.setView(view);
		window.display();
	}

	return 0;
}
