#pragma once
#include "../Setup/Setup.h"
#include "./Gui/ArrowControl.hpp"

class EventHandler
{
private:
	sf::RenderWindow& window;
	sf::View& view;
	ArrowControl& arrowControl;

public:
	EventHandler(sf::RenderWindow& window, sf::View& view, ArrowControl& arrowControl);
	void process(sf::Event& event);
};
