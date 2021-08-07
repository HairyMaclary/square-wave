#include "./EventHandler/EventHandler.h"
#include "./Setup/Setup.h" // window dimensions, views, constants
#include "Circle/Circle.hpp"
#include <math.h> /* sin, cos */

main()
{
	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view, "Fourier Square Wave Generation");

	Circle circle(window, 0);

	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, view);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			handler.process(event);
		}

		window.clear(sf::Color(0, 0, 0));

		circle.update(deltaTime);
		circle.draw();
		window.setView(view);
		window.display();
	}
	return 0;
}
