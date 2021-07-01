#include "Platform/Platform.hpp"
#include <iostream>

const float windowWidth { 1200.0f };
const float windowHeight { 900.0f };

void resizedView(const sf::RenderWindow& window, sf::View& view);

void resizedView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(windowWidth * aspectRatio, windowHeight * aspectRatio);
}

main()
{
	util::Platform platform;
	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Asteroids");
	platform.setIcon(window.getSystemHandle());

	sf::FloatRect visibleArea(-windowWidth / 2, -windowHeight / 2, windowWidth, windowHeight);
	sf::View view(visibleArea);

	const float radius = 40.0f;
	sf::CircleShape ship((int)radius, 3);
	ship.setFillColor(sf::Color(0, 0, 0));
	ship.setOutlineThickness(2);
	ship.setOutlineColor(sf::Color(250, 255, 255));
	ship.setOrigin(sf::Vector2f(radius, 40.0f));

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
					resizedView(window, view);
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
		window.setView(view);
		window.display();
	}

	return 0;
}
