#include "./Lasers.h"
#include "../src/Asteroid/Asteroid.h"
#include "../src/Ship/Ship.h"
#include "./Laser.h"

Lasers::Lasers(sf::RenderWindow& renderWindow, Ship& craft) :
	window { renderWindow },
	ship { craft }
{
	if (!destructionSoundBuffer.loadFromFile("src/sounds/break.wav"))
	{
		std::cout << "Bugger, break sound load did not work" << std::endl;
	}

	destructionSound.setBuffer(destructionSoundBuffer);

	if (!boltSoundBuffer.loadFromFile("src/sounds/laser.wav"))
	{
		std::cout << "Bugger, laser sound load did not work" << std::endl;
	}

	boltSound.setBuffer(boltSoundBuffer);
}

void Lasers::checkKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		Laser* ptr = new Laser(window, ship.position, ship.heading);
		bolts.push_back(ptr);
		boltSound.play();
	}
}

void Lasers::draw(float deltaTime)
{
	// velocity is not frame or machine specific
	runningTime += deltaTime;
	if (runningTime > maxTime)
	{
		runningTime = 0;
		checkKeys();
	}

	deleteOldBolts();
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
			// then erase() would fail. It was essentially moving elements of the vector
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

bool Lasers::hits(Asteroid& asteroid)
{
	std::vector<Laser*>::iterator iterator;
	for (iterator = bolts.begin(); iterator != bolts.end();)
	{
		const sf::FloatRect& bounds = (*iterator)->getGlobalBounds();
		if (asteroid.hit(bounds))
		{
			delete (*iterator);
			(*iterator) = nullptr;
			iterator = bolts.erase(iterator);
			destructionSound.play();
			return true;
		}
		else
		{
			++iterator;
		}
	}
	return false;
}
