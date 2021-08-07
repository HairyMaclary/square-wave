
#ifndef SETUP_H
#define SETUP_H

namespace window
{
extern float width;
extern float height;
}

namespace constants
{
extern const float pi;
extern const float maxTime;
}

void resizedView(const sf::RenderWindow& window, sf::View& view);
void generateSetup(sf::RenderWindow& window, sf::View& view, std::string windowTitle);

#endif