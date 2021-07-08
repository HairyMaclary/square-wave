#pragma once
#include "../Setup/Setup.h"
#include "./Ship/Ship.h"

class EventHandler
{
private:
	sf::RenderWindow& window;
	Ship& ship;

public:
	EventHandler(sf::RenderWindow& window, Ship& ship);
	void process(sf::Event& event);
};
