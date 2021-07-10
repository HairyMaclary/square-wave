
#ifndef SETUP_H
#define SETUP_H

extern float windowWidth;
extern float windowHeight;

void resizedView(const sf::RenderWindow& window);
void generateSetup(sf::RenderWindow& window, sf::View& view);

#endif