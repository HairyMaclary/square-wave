#include "Platform/Platform.hpp"
#include <iostream>

main()
{
	util::Platform platform;

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	float windowWidth { 1200.0f };
	float windowHeight { 900.0f };
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Asteroids");
	platform.setIcon(window.getSystemHandle());

	sf::CircleShape ship(80, 3);
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	ship.setPosition(206.0f, 206.0f);

	float deltaTime = 0.0f;

	std::cout << deltaTime << std::endl;

	sf::Clock clock;

	sf::Event event;

	while (window.isOpen())
	{

		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					std::cout << "New window width: " << event.size.width << " new height: " << event.size.height << std::endl;
					break;
				case sf::Event::TextEntered:
					printf("%c", event.text.unicode);
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Key::A)
					{
						// player.move(-1.00f, 0.0f);
					}
					if (event.key.code == sf::Keyboard::Key::D)
					{
						// player.move(1.00f, 0.0f);
					}
					break;
				case sf::Event::GainedFocus:
				case sf::Event::KeyReleased:
				case sf::Event::MouseWheelMoved:
				case sf::Event::MouseWheelScrolled:
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						// player.setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
					}
					break;
				case sf::Event::MouseButtonReleased:
				case sf::Event::MouseMoved:
				case sf::Event::MouseEntered:
				case sf::Event::MouseLeft:
				case sf::Event::JoystickButtonPressed:
				case sf::Event::JoystickButtonReleased:
				case sf::Event::JoystickMoved:
				case sf::Event::JoystickConnected:
				case sf::Event::JoystickDisconnected:
				case sf::Event::TouchBegan:
				case sf::Event::TouchMoved:
				case sf::Event::TouchEnded:
				case sf::Event::SensorChanged:
				case sf::Event::Count:
				case sf::Event::LostFocus:
				default:
					break;
			}
		}

		// move an object much faster: use the existing object and not an event

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		// {
		// 	player.move(-1.00f, 0.0f);
		// }

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		// {
		// 	player.move(1.00f, 0.0f);
		// }

		// if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		// {
		// 	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		// 	int mouseX = static_cast<float>(mousePosition.x);
		// 	int mouseY = static_cast<float>(mousePosition.y);
		// 	player.setPosition(mouseX, mouseY);
		// }

		window.clear(sf::Color(0, 0, 0));
		window.draw(ship);
		window.display();
	}

	return 0;
}
