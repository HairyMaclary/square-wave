#include "..\src\Grid\Grid.h"
#include ".\Utility\Animation.h"
#include ".\Utility\MapData.h"
#include "Platform/Platform.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	float windowWidth { 1200.0f };
	float windowHeight { 900.0f };
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Conway");
	platform.setIcon(window.getSystemHandle());

	const int maxSqaures1D { 100 };
	Grid grid { windowWidth, windowHeight, maxSqaures1D, window };
	grid.draw();

	// sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
	// player.setPosition(206.0f, 206.0f);
	// player.setFillColor(sf::Color::Green);
	// player.setOrigin(50.0f, 50.0f);

	// sf::Texture playerTexture;
	// playerTexture.loadFromFile("content/tux_from_linux.png");
	// player.setTexture(&playerTexture);

	// sf::Vector2u textureSize { playerTexture.getSize() };

	// textureSize.x /= 3;
	// textureSize.y /= 9;

	// Animation animation { 3, textureSize, 5, player };
	float deltaTime = 0.0f;
	// animation.updatePosition(deltaTime);

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

		window.clear(sf::Color(150, 150, 150));
		// animation.updatePosition(deltaTime);
		// window.draw(player);
		grid.draw();
		window.display();
	}

	return 0;
}
