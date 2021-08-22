#include "./EventHandler/EventHandler.h"
#include "./Gui/ArrowControl.hpp"
#include "./Gui/Slider.hpp"
#include "./Setup/Setup.h" // window dimensions, views, constants
#include "Circle/Circle.hpp"
#include "Wave/Wave.hpp"
#include <math.h> /* sin, cos */

main()
{
	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view, "Fourier Square Wave Generation");
	view.move(600.0f, 0.f); // move the circles so that we can see more wave

	// essentially the number of super-imposed sine waves
	uint iterations = 3;

	// using std::vector because we need i in the circle constructor
	std::vector<Circle*> circles;
	for (uint i = 0; i < iterations; ++i)
	{
		circles.push_back(new Circle(window, i));
	}

	Wave wave(window);

	// line to connect the last point with the wave
	sf::VertexArray line { sf::Lines, 2 };
	line[0].color = sf::Color(255.f, 255.f, 255.f, 100.f);
	line[1].color = sf::Color(255.f, 255.f, 255.f, 100.f);

	// slider to adjust the number of component waves
	ArrowControl arrowControl(window, iterations);

	float runningTime { 0 };
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, view, arrowControl);

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
			const int updateDifference = (int)circles.size() - (int)iterations;
			// if the count has changed only add/remove one circle system per frame. Improve performance.
			if (updateDifference < 0)
			{
				float currentRadians = (circles[0])->getRadians();
				circles.push_back(new Circle(window, circles.size(), currentRadians));
			}
			else if (updateDifference > 0)
			{
				std::vector<Circle*>::iterator it(circles.end() - 1);
				delete *it;
				circles.pop_back();
			}

			// origin for the first circle
			float x = 0;
			float y = 0;

			std::vector<Circle*>::iterator it;
			for (it = circles.begin(); it != circles.end(); ++it)
			{
				(*it)->update(x, y);
			}

			wave.addValue(y);
			sf::Vector2f lastWavePos = wave.getLastPosition();

			line[0].position = sf::Vector2f(x, y);
			line[1].position = lastWavePos;

			runningTime = 0;
		}

		std::vector<Circle*>::iterator it;
		for (it = circles.begin(); it != circles.end(); ++it)
		{
			(*it)->draw();
		}

		wave.update();
		wave.draw();
		arrowControl.update();
		arrowControl.draw();
		window.draw(line);

		window.setView(view);
		window.display();
	}

	// memory clean up
	std::vector<Circle*>::iterator it;
	for (it = circles.begin(); it != circles.end(); ++it)
	{
		delete *it;
	}
	return 0;
}
