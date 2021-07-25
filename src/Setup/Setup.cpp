
#include "./Setup.h"
#include "Platform/Platform.hpp"

float windowWidth = 1200.0f;
float windowHeight = 900.0f;

namespace constants
{
extern const float pi { float(std::atan(1) * 4) };
}

void resizedView(const sf::RenderWindow& window, sf::View& view)
{
	windowWidth = float(window.getSize().x);
	windowHeight = float(window.getSize().y);
	view.setSize(windowWidth, windowHeight);
}

void generateSetup(sf::RenderWindow& window, sf::View& view)
{
	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Use the screenScalingFactor
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Asteroids", sf::Style::Default, settings);
	platform.setIcon(window.getSystemHandle());

	sf::Vector2f center(0, 0);
	sf::Vector2f size(windowWidth, windowHeight);
	view.setCenter(center);
	view.setSize(size);
}