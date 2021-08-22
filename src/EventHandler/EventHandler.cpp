#include "./EventHandler.h"
#include "./Gui/ArrowControl.hpp"

EventHandler::EventHandler(sf::RenderWindow& window, sf::View& view, ArrowControl& arrowControl) :
	window { window },
	view { view },
	arrowControl { arrowControl }
{
}

void EventHandler::process(sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			resizedView(window, view);
			break;
		case sf::Event::TextEntered:
			printf("%c", event.text.unicode);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Key::Up)
			{
				arrowControl.increase();
			}
			if (event.key.code == sf::Keyboard::Key::Down)
			{
				arrowControl.decrease();
			}
			break;
		case sf::Event::GainedFocus:
		case sf::Event::KeyReleased:
		case sf::Event::MouseWheelMoved:
		case sf::Event::MouseWheelScrolled:
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// player.setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			}
			break;
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseMoved:
		case sf::Event::MouseEntered:
		case sf::Event::MouseLeft:
		case sf::Event::JoystickButtonPressed:
		case sf::Event::JoystickButtonReleased:
		case sf::Event::JoystickMoved:
		case sf::Event::JoystickConnected:
		case sf::Event::JoystickDisconnected:
		case sf::Event::TouchBegan:
		case sf::Event::TouchMoved:
		case sf::Event::TouchEnded:
		case sf::Event::SensorChanged:
		case sf::Event::Count:
		case sf::Event::LostFocus:
		default:
			break;
	}
}