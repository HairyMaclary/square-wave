#pragma once
#include "../src/Ship/Ship.h"
#include "./Laser.h"
#include <vector>

class Lasers
{
private:
	sf::RenderWindow& window;
	Ship& ship;
	std::vector<Laser*> bolts;

	void checkKeys();
	void deleteOldBolts();

public:
	Lasers(sf::RenderWindow& window, Ship& craft);
	void draw();
};