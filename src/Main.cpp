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
	sf::CircleShape circle(200.f, 80);
	circle.setOrigin(200.0f, 200.0f);

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

		window.clear(sf::Color(0, 0, 0));
		window.draw(circle);
		ship.draw();
		window.setView(view);
		window.display();
	}

	return 0;
}
