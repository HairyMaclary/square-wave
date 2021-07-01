
#include "./Setup.h"
#include "Platform/Platform.hpp"

extern const float windowWidth { 1200.0f };
extern const float windowHeight { 900.0f };

void resizedView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(windowWidth * aspectRatio, windowHeight * aspectRatio);
}

void generateSetup(sf::RenderWindow& window, sf::View& view)
{
	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// Use the screenScalingFactor
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), "Asteroids");
	platform.setIcon(window.getSystemHandle());

	sf::Vector2f center(-windowWidth / 40, -windowHeight / 40); // don't know why this cant be devided by 2.
	const sf::Vector2f size(windowWidth, windowHeight);
	view.setCenter(center);
	view.setSize(size);
}