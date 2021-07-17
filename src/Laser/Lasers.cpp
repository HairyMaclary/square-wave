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
			// When bolts was an array of Lasers instead of an array of pointers to lasers
			// then erase() would fail. It was essentially moving elements of the array
			// around, and since the window member was a reference, it is treated as a
			// const and could not be moved. Another option was to implement a
			// a move-assignment operator ( T& operator = (T&&) ) ,
			// or a copy-assignment operator (T& operator = (const T&)).
			// see https://stackoverflow.com/questions/43307277/c-vector-erase-instance-of-a-class-with-const-int-gives-attempting-to-refere
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