
#ifndef SETUP_H
#define SETUP_H

extern float windowWidth;
extern float windowHeight;

namespace constants
{
extern const float pi;
}

void resizedView(const sf::RenderWindow& window, sf::View& view);
void generateSetup(sf::RenderWindow& window, sf::View& view);

#endif