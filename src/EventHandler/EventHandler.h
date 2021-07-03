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
