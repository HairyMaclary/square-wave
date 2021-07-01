
#ifndef SETUP_H
#define SETUP_H

extern const float windowWidth;
extern const float windowHeight;

void resizedView(const sf::RenderWindow& window, sf::View& view);
void generateSetup(sf::RenderWindow& window, sf::View& view);

#endif