#pragma once

#include "../Setup/Setup.h"

class EventHandler
{
private:
	sf::RenderWindow& window;
	sf::View& view;

public:
	EventHandler(sf::RenderWindow& window, sf::View& view);

	void process(sf::Event& event);
};

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