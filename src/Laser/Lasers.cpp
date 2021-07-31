#include "./Lasers.h"
#include "../src/Asteroid/Asteroid.h"
#include "../src/Ship/Ship.h"
#include "./Laser.h"
#include <list> // std::list

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

void Lasers::update(float deltaTime)
{
	runningTime += deltaTime;
	if (runningTime > maxTime)
	{
		runningTime = 0;
		checkKeys();
	}

	deleteOldBolts();
}

void Lasers::draw(float deltaTime)
{
	update(deltaTime);

	std::list<Laser*>::iterator it;
	for (it = bolts.begin(); it != bolts.end(); ++it)
	{
		(*it)->draw();
	}
}
void Lasers::deleteOldBolts()
{
	std::list<Laser*>::iterator it;
	for (it = bolts.begin(); it != bolts.end();)
	{
		if ((*it)->offscreen())
		{
			// When bolts was an array of Lasers instead of an array of pointers to lasers
			// then erase() would fail. It was essentially moving elements of the vector
			// around, and since the window member was a reference, it is treated as a
			// const and could not be moved. Another option was to implement a
			// a move-assignment operator ( T& operator = (T&&) ) ,
			// or a copy-assignment operator (T& operator = (const T&)).
			// see https://stackoverflow.com/questions/43307277/c-vector-erase-instance-of-a-class-with-const-int-gives-attempting-to-refere
			delete (*it);
			(*it) = nullptr;
			it = bolts.erase(it); // erase returns back the next position
		}
		else
		{
			++it;
		}
	}
}

bool Lasers::hits(Asteroid& asteroid)
{
	std::list<Laser*>::iterator it;
	for (it = bolts.begin(); it != bolts.end();)
	{
		sf::Vector2f asteroidPos = asteroid.getPosition();
		sf::Vector2f laserPos = (*it)->getPosition();
		sf::Vector2f diffVec = laserPos - asteroidPos;
		float distance = sqrt(diffVec.x * diffVec.x + diffVec.y * diffVec.y);
		float asteroidRadius = asteroid.getRadius();
		// once the the laser is approximatley within 20px of the asteroid
		// then use fine-grained/expensive collision detection.
		const bool isNearby = distance < asteroidRadius + (*it)->getBoltLength() + 20;
		if (isNearby)
		{
			const sf::FloatRect& bounds = (*it)->getGlobalBounds();
			if (asteroid.hit(bounds))
			{
				delete (*it);
				(*it) = nullptr;
				it = bolts.erase(it);
				destructionSound.play();
				return true;
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}
	return false;
}
