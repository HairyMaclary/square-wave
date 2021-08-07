#include "./EventHandler/EventHandler.h"
#include "./Setup/Setup.h" // window dimensions, views, constants
#include "Circle/Circle.hpp"
#include <math.h> /* sin, cos */

main()
{
	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view, "Fourier Square Wave Generation");
	view.move(600.0f, 0.f);

	// essentially the number of superimposed sound waves
	const uint maxIterations = 3;

	// using std::vector because we need i in the circle constructor
	std::vector<Circle*> circles;

	for (uint i = 0; i < maxIterations; ++i)
	{
		circles.push_back(new Circle(window, i));
	}

	float runningTime { 0 };
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

		runningTime += deltaTime;
		if (runningTime > constants::maxTime)
		{
			// origin for the first circle
			float x = 0;
			float y = 0;

			std::vector<Circle*>::iterator it;
			for (it = circles.begin(); it != circles.end(); ++it)
			{
				(*it)->update(x, y);
			}

			runningTime = 0;
		}

		std::vector<Circle*>::iterator it;
		for (it = circles.begin(); it != circles.end(); ++it)
		{
			(*it)->draw();
		}

		window.setView(view);
		window.display();
	}
	return 0;
}
