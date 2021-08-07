
#include "./Setup.h"
#include "Platform/Platform.hpp"
#include <string>

namespace window
{
float width = 1200.0f;
float height = 900.0f;
}

namespace constants
{
extern const float pi { float(std::atan(1) * 4) };
extern const float maxTime { 0.0167 }; // 60 fps
}

void resizedView(const sf::RenderWindow& window, sf::View& view)
{
	window::width = float(window.getSize().x);
	window::height = float(window.getSize().y);
	view.setSize(window::width, window::height);
}

void generateSetup(sf::RenderWindow& window, sf::View& view, std::string windowTitle)
{
	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Use the screenScalingFactor
	window.create(sf::VideoMode(window::width * screenScalingFactor, window::height * screenScalingFactor), windowTitle, sf::Style::Default, settings);
	platform.setIcon(window.getSystemHandle());

	sf::Vector2f center(0, 0);
	sf::Vector2f size(window::width, window::height);
	view.setCenter(center);
	view.setSize(size);
}