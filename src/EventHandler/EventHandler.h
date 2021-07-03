#pragma once

#include "../Setup/Setup.h"

class EventHandler
{
private:
	sf::RenderWindow& window;

public:
	EventHandler(sf::RenderWindow& window);

	void process(sf::Event& event);
};
