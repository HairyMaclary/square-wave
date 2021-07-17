#include "./Lasers.h"
#include "../src/Ship/Ship.h"
#include "./Laser.h"

Lasers::Lasers(sf::RenderWindow& renderWindow, Ship& craft) :
	window { renderWindow },
	ship { craft }
{}

void Lasers::checkKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		Laser* ptr = new Laser(window, ship.position, ship.heading);
		bolts.push_back(ptr);
	}
}

void Lasers::draw()
{
	deleteOldBolts();
	checkKeys();
	for (uint i = 0; i < bolts.size(); i++)
	{
		bolts[i]->draw();
	}
}
void Lasers::deleteOldBolts()
{
	std::vector<Laser*>::iterator position;
	for (position = bolts.begin(); position != bolts.end();)
	{
		if ((*position)->offscreen())
		{
			// TODO Is this enough to prevent memory leaks?
			delete (*position);
			(*position) = nullptr;
			position = bolts.erase(position); // erase returns back the next position
		}
		else
		{
			++position;
		}
	}
}