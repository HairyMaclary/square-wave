#include "./EventHandler/EventHandler.h"
#include "./Setup/Setup.h" // window dimensions, views, constants
#include <math.h>		   /* sin, cos */

main()
{
	sf::RenderWindow window;
	sf::View view;
	generateSetup(window, view, "Fourier Square Wave Generation");

	const float radius = 200.0f;
	sf::CircleShape circ(radius);
	circ.setOutlineThickness(1.f);
	circ.setOutlineColor(sf::Color(255.f, 255.f, 255.f, 100.f));
	circ.setFillColor(sf::Color::Black);
	circ.setOrigin(radius, radius);
	circ.setPointCount(100);

	const float pointRadius = 6.f;
	sf::CircleShape point(pointRadius);
	point.setOutlineThickness(1.f);
	point.setOutlineColor(sf::Color::White);
	point.setFillColor(sf::Color::White);
	point.setOrigin(pointRadius, pointRadius);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(0.f, 0.f);
	line[1].position = sf::Vector2f(100.f, 100.f);
	line[0].color = sf::Color(255.f, 255.f, 255.f, 100.f);
	line[1].color = sf::Color(255.f, 255.f, 255.f, 100.f);

	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event event;
	EventHandler handler(window, view);

	float runningTime = 0;
	const float maxTime = 0.0167; // 60 fps
	float radians = 0;
	const float dampner = 0.1;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			handler.process(event);
		}

		runningTime += deltaTime;
		if (runningTime > maxTime)
		{
			radians += 2 * constants::pi * maxTime * dampner;
			float x = radius * cos(radians);
			float y = radius * sin(radians);
			point.setPosition(x, y);
			runningTime = 0;
			line[1].position = sf::Vector2f(x, y);
		}

		window.clear(sf::Color(0, 0, 0));
		window.draw(circ);
		window.draw(point);
		window.draw(line);
		window.setView(view);
		window.display();
	}
	return 0;
}
