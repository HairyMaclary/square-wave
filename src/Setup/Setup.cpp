
#include "./Setup.h"
#include "Platform/Platform.hpp"

extern const float windowWidth { 1200.0f };
extern const float windowHeight { 900.0f };

void resizedView(const sf::RenderWindow& window, sf::View& view)
{
	float newWindowWidth = float(window.getSize().x);
	float newWindowHeight = float(window.getSize().y);
	view.setSize(newWindowWidth, newWindowHeight);
}

void generateSetup(sf::RenderWindow& window, sf::View& view)
{
	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// Use the screenScalingFactor
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Asteroids");
	platform.setIcon(window.getSystemHandle());

	sf::Vector2f center(0, 0);
	sf::Vector2f size(windowWidth, windowHeight);
	view.setCenter(center);
	view.setSize(size);
}