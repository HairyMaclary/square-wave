#pragma once
#include "../Setup/Setup.h"
#include "./Ship/Ship.h"

class EventHandler
{
private:
	sf::RenderWindow& window;
	Ship& ship;
	sf::View& view;

public:
	EventHandler(sf::RenderWindow& window, Ship& ship, sf::View& view);
	void process(sf::Event& event);
};
